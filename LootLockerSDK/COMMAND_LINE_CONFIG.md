# LootLocker Unreal SDK - Command Line Configuration

## Overview

The LootLocker Unreal SDK supports command line configuration overrides, allowing you to configure the SDK at runtime through command line arguments. This is useful for CI/CD pipelines, automated testing, and different deployment environments.

## Enabling Command Line Settings

Command line configuration is enabled by default. To disable it, set `bEnableCommandLineSettings = false` in `LootLockerSDK.Build.cs`.

## Supported Command Line Arguments

### API Configuration

- **`-lootlockerkey=<key>`** or **`-apikey=<key>`**
  - Sets the LootLocker API key
  - Example: `-lootlockerkey=dev_1234567890abcdef`

- **`-lootlockerdomainkey=<key>`** or **`-domainkey=<key>`**
  - Sets the LootLocker Domain key
  - Example: `-lootlockerdomainkey=my-domain-key`

- **`-lootlockerversion=<version>`** or **`-gameversion=<version>`**
  - Sets the game version (must follow semantic versioning: X.Y.Z.B)
  - Example: `-lootlockerversion=1.2.3.4`

### Logging Configuration

- **`-lootlockerlogging=<level>`** or **`-loglevel=<level>`**
  - Sets the log level
  - Valid values: `NoLogging`, `Error`, `Warning`, `Verbose`, `All`
  - Example: `-lootlockerlogging=Verbose`

- **`-lootlockerlogfile=<filename>`** or **`-logfile=<filename>`**
  - Enables file logging and sets the log file name
  - Example: `-lootlockerlogfile=MyGameLog`

- **`-lootlockerlogoutside`** or **`-logoutside`**
  - Enables logging outside of the editor
  - Example: `-lootlockerlogoutside`

- **`-lootlockernologoutside`** or **`-nologoutside`**
  - Disables logging outside of the editor
  - Example: `-lootlockernologoutside`

### Token Refresh Configuration

- **`-lootlockerallowrefresh`** or **`-allowtokenrefresh`**
  - Enables token refresh
  - Example: `-lootlockerallowrefresh`

- **`-lootlockerdisablerefresh`** or **`-disabletokenrefresh`**
  - Disables token refresh
  - Example: `-lootlockerdisablerefresh`

## Usage Examples

### Running a Build with Command Line Arguments

**Windows:**
```cmd
MyGame.exe -lootlockerkey=dev_abc123 -lootlockerversion=1.0.0 -lootlockerlogging=Verbose
```

**Linux:**
```bash
./MyGame -lootlockerkey=dev_abc123 -lootlockerversion=1.0.0 -lootlockerlogging=Verbose
```

**macOS:**
```bash
./MyGame.app/Contents/MacOS/MyGame -lootlockerkey=dev_abc123 -lootlockerversion=1.0.0 -lootlockerlogging=Verbose
```

### CI/CD Pipeline Example

In your CI/CD pipeline, you can configure different environments:

```yaml
# Development Environment
./MyGame -lootlockerkey=$DEV_API_KEY -lootlockerversion=$BUILD_VERSION -lootlockerlogging=Verbose

# Staging Environment
./MyGame -lootlockerkey=$STAGING_API_KEY -lootlockerversion=$BUILD_VERSION -lootlockerlogging=Warning

# Production Environment
./MyGame -lootlockerkey=$PROD_API_KEY -lootlockerversion=$BUILD_VERSION -lootlockerlogging=Error
```

## Implementation Details

Command line arguments are parsed in the `PostInitProperties()` method of `ULootLockerConfig`. This ensures that command line overrides are applied as soon as the config object is initialized, before any SDK functionality is used.

The feature is controlled by the `LOOTLOCKER_COMMANDLINE_SETTINGS` preprocessor define, which is automatically added when `bEnableCommandLineSettings` is set to `true` in the Build.cs file.

## Feature Parity with Unity SDK

This implementation provides feature parity with the Unity SDK's command line configuration system, using similar argument names and behavior patterns adapted for Unreal Engine conventions.

## Notes

- Command line arguments override values from the config file (DefaultGame.ini)
- Overrides are applied at runtime and are not persisted
- Invalid values (e.g., invalid semantic version) will be validated according to existing validation rules
- All command line argument names are case-insensitive
