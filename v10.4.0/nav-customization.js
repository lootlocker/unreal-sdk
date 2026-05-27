/**
 * nav-customization.js - LootLocker Unreal SDK sidebar nav customizer.
 *
 * Phase 1 (synchronous, before DOMContentLoaded):
 *   Patches the NAVTREE data structure so that file-level enum entries
 *   appear as children of "Structs" or "Classes" instead of floating at
 *   the root level. This runs before initNavTree() processes the data,
 *   so doxygen handles the items natively (correct indent, expand/collapse,
 *   search sync).
 *
 * Phase 2 (after DOMContentLoaded + MutationObserver):
 *   1. Hides the redundant root label and the API Reference breadcrumb link.
 *   2. Expands Topics and hoists every topic group to root level.
 *   3. Strips the fully-qualified C++ prefix from every nav label,
 *      preserving the full name as a hover tooltip.
 */

/* Phase 1: Patch NAVTREE data before the tree renders */
(function patchNavTreeData() {
  if (typeof NAVTREE === 'undefined' || !Array.isArray(NAVTREE[0])) return;

  var rootChildren = NAVTREE[0][2];
  if (!Array.isArray(rootChildren)) return;

  var structsEntry = null;
  for (var i = 0; i < rootChildren.length; i++) {
    if (rootChildren[i][0] === 'Structs') { structsEntry = rootChildren[i]; break; }
  }
  if (!structsEntry) return;

  var structsKids = Array.isArray(structsEntry[2]) ? structsEntry[2] : [];

  var toKeep = [];
  var toMove = [];
  for (var j = 0; j < rootChildren.length; j++) {
    var item  = rootChildren[j];
    var label = item[0] || '';
    if (label === 'Structs' || label === 'Classes' || label === 'Topics' ||
        label.indexOf('API Reference') !== -1 ||
        label.indexOf('Overview') !== -1) {
      toKeep.push(item);
    } else if (label) {
      toMove.push(item);
    } else {
      toKeep.push(item);
    }
  }

  if (toMove.length === 0) return;

  structsEntry[2] = structsKids.concat(toMove);
  NAVTREE[0][2] = toKeep;
}());

/* Phase 2: DOM restructuring after the nav tree renders */
(function () {
  'use strict';

  var INDENT = 16;

  function getLabel(li) {
    var s = li.querySelector(':scope > .item .label a span');
    return s ? s.textContent.trim() : '';
  }

  function getToggle(li) {
    return li.querySelector(':scope > .item > a[href="javascript:void(0)"]');
  }

  function getChildrenUL(li) {
    return li.querySelector(':scope > ul.children_ul');
  }

  function setIndentLevel(li, level) {
    var expSpan = li.querySelector(':scope > .item > a > span.arrow');
    if (expSpan) { expSpan.style.paddingLeft = (INDENT * level) + 'px'; return; }
    var leafSpan = li.querySelector(':scope > .item > span.arrow');
    if (leafSpan) { leafSpan.style.width = (INDENT * (level + 1)) + 'px'; }
  }

  function shiftIndentBy(li, delta) {
    var expSpan = li.querySelector(':scope > .item > a > span.arrow');
    if (expSpan) {
      var v = parseInt(expSpan.style.paddingLeft) || 0;
      expSpan.style.paddingLeft = Math.max(0, v + delta * INDENT) + 'px';
      return;
    }
    var leafSpan = li.querySelector(':scope > .item > span.arrow');
    if (leafSpan) {
      var w = parseInt(leafSpan.style.width) || 0;
      leafSpan.style.width = Math.max(INDENT, w + delta * INDENT) + 'px';
    }
  }

  function shiftSubtree(ul, delta) {
    Array.prototype.forEach.call(ul.children, function (li) {
      shiftIndentBy(li, delta);
      var child = getChildrenUL(li);
      if (child) shiftSubtree(child, delta);
    });
  }

  var STRIPPED_ATTR = 'data-ll-stripped';

  /**
   * Strip the C++ scope prefix from a qualified name.
   * Handles both '::' (C++ namespaces) and '.' (Doxygen sometimes uses '.').
   * e.g. "LootLocker::FLootLockerResponse" → "FLootLockerResponse"
   *      "StartGuestSession(FLootLockerSessionResponse)" → unchanged (no prefix)
   */
  function lastSegment(label) {
    // Handle function signatures: strip prefix only from the base name
    var parenIdx = label.indexOf('(');
    if (parenIdx !== -1) {
      var before = label.slice(0, parenIdx);
      var after  = label.slice(parenIdx);
      var colonIdx = before.lastIndexOf('::');
      if (colonIdx !== -1) return before.slice(colonIdx + 2) + after;
      var dotIdx = before.lastIndexOf('.');
      if (dotIdx !== -1) return before.slice(dotIdx + 1) + after;
      return label;
    }
    // No parens: strip last scope segment
    var colonIdx = label.lastIndexOf('::');
    if (colonIdx !== -1) return label.slice(colonIdx + 2);
    var dotIdx = label.lastIndexOf('.');
    if (dotIdx !== -1) return label.slice(dotIdx + 1);
    return label;
  }

  function stripLabel(li) {
    if (li.getAttribute(STRIPPED_ATTR)) return;
    li.setAttribute(STRIPPED_ATTR, '1');
    var s = li.querySelector(':scope > .item .label a span');
    if (!s) return;
    var full  = s.textContent.trim();
    var short = lastSegment(full);
    if (short !== full) { s.title = full; s.textContent = short; }
  }

  function stripAll(root) {
    root.querySelectorAll('li').forEach(stripLabel);
  }

  /** Hide FXxx / EXxx type entries inside topic group nodes (structs, delegates, enums). */
  function hideTypesInTopics(root) {
    root.querySelectorAll('[data-ll-topic-group] li').forEach(function (li) {
      var lbl = getLabel(li) || '';
      if (/^[FE][A-Z]/.test(lbl)) { li.style.display = 'none'; }
    });
  }

  var globalShiftApplied = false;
  var topicsHandled      = false;

  function restructure() {
    var contentsDiv = document.getElementById('nav-tree-contents');
    if (!contentsDiv) return;

    var outerUL = contentsDiv.querySelector(':scope > ul');
    if (!outerUL) return;
    var wrapperLi = outerUL.querySelector(':scope > li');
    if (!wrapperLi) return;

    var wrapperItem = wrapperLi.querySelector(':scope > .item');
    if (wrapperItem) wrapperItem.style.display = 'none';

    var childrenUL = getChildrenUL(wrapperLi);
    if (!childrenUL) return;
    childrenUL.style.display = 'block';

    if (!globalShiftApplied) {
      globalShiftApplied = true;
      shiftSubtree(childrenUL, -1);
    }

    var kids     = Array.prototype.slice.call(childrenUL.children);
    var topicsLi = null;
    for (var i = 0; i < kids.length; i++) {
      var li  = kids[i];
      var lbl = getLabel(li);
      if (lbl === 'Topics') { topicsLi = li; continue; }
      if (li.dataset.llTopicGroup) continue;
      if (lbl.indexOf('API Reference') !== -1 || lbl.indexOf('Overview') !== -1) {
        li.style.display = 'none';
      }
    }

    if (!topicsHandled && topicsLi) {
      var topicsChildUL = getChildrenUL(topicsLi);

      if (!topicsChildUL || topicsChildUL.children.length === 0) {
        if (!topicsLi.dataset.llTopicsClicked) {
          topicsLi.dataset.llTopicsClicked = '1';
          var toggle = getToggle(topicsLi);
          if (toggle) toggle.click();
        }
        return;
      }

      Array.prototype.slice.call(topicsChildUL.children).forEach(function (groupLi) {
        setIndentLevel(groupLi, 0);
        groupLi.dataset.llTopicGroup = '1';
        childrenUL.insertBefore(groupLi, topicsLi);
      });

      topicsLi.style.display = 'none';
      topicsHandled = true;
    }

    stripAll(contentsDiv);
    hideTypesInTopics(contentsDiv);
  }

  function fixNewItem(li) {
    stripLabel(li);
    if (li.getAttribute('data-ll-indent-fixed')) return;
    li.setAttribute('data-ll-indent-fixed', '1');
    if (li.closest('[data-ll-topic-group]')) {
      setIndentLevel(li, 1);
      // Within a topic group, hide type entries (structs, delegates, enums).
      // All LootLocker types follow UE naming conventions:
      //   F<Upper> — USTRUCT / delegate typedef
      //   E<Upper> — UENUM
      // Interface methods (the only items we want) are plain camelCase.
      var lbl = getLabel(li) || '';
      if (/^[FE][A-Z]/.test(lbl)) { li.style.display = 'none'; return; }
    } else {
      shiftIndentBy(li, -1);
    }
  }

  function onNewNodes(addedNodes) {
    addedNodes.forEach(function (node) {
      if (node.nodeType !== 1) return;
      var lis = node.tagName === 'LI' ? [node] : [];
      Array.prototype.push.apply(lis, node.querySelectorAll('li'));
      lis.forEach(fixNewItem);
    });
  }

  function init() {
    var navTree = document.getElementById('nav-tree');
    if (!navTree) { setTimeout(init, 200); return; }

    var debounce;
    var obs = new MutationObserver(function (mutations) {
      var added = [];
      mutations.forEach(function (m) { m.addedNodes.forEach(function (n) { added.push(n); }); });
      if (added.length) onNewNodes(added);
      clearTimeout(debounce);
      debounce = setTimeout(restructure, 80);
    });
    obs.observe(navTree, { childList: true, subtree: true });

    setTimeout(restructure, 250);
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
}());
