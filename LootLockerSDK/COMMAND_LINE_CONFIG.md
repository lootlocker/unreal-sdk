# LootLocker Unreal SDK - Command Line Configuration

## Overview

The LootLocker Unreal SDK supports command line configuration overrides using Unreal Engine's built-in INI override system. This allows you to configure the SDK at runtime through command line arguments, which is useful for CI/CD pipelines, automated testing, and different deployment environments.

## How It Works

The LootLocker SDK uses Unreal Engine's config system (`UCLASS(Config = Game)` with `UPROPERTY(Config, ...)`). All configuration properties are automatically saved to and loaded from INI files, and Unreal Engine provides built-in command line override support.

Following [Epic's official documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/configuration-files-in-unreal-engine#overrideconfigurationfromthecommand-line), you can override any config property using the `-ini:` command line syntax.

## Command Line Syntax

Use the following format to override LootLocker config values:

```
-ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:PropertyName=Value
```

## Supported Configuration Properties

All `UPROPERTY(Config, ...)` properties in `ULootLockerConfig` can be overridden from the command line:

### API Configuration

- **LootLockerGameKey** - The LootLocker API key
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=dev_1234567890abcdef
  ```

- **DomainKey** - The LootLocker Domain key
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:DomainKey=my-domain-key
  ```

- **GameVersion** - The game version (must follow semantic versioning: X.Y.Z.B)
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:GameVersion=1.2.3.4
  ```

- **AllowTokenRefresh** - Enable/disable token refresh (true/false)
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:AllowTokenRefresh=true
  ```

### Logging Configuration

- **LootLockerLogLevel** - The log level (0=NoLogging, 1=Error, 2=Warning, 3=Verbose)
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerLogLevel=3
  ```

- **LogOutsideOfEditor** - Enable logging outside the editor (true/false)
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LogOutsideOfEditor=true
  ```

- **bEnableFileLogging** - Enable file logging (true/false)
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:bEnableFileLogging=true
  ```

- **LogFileName** - The log file name
  ```bash
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LogFileName=MyGameLog
  ```

## Usage Examples

### Single Property Override

**Windows:**
```cmd
MyGame.exe -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=dev_abc123
```

**Linux:**
```bash
./MyGame -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=dev_abc123
```

**macOS:**
```bash
./MyGame.app/Contents/MacOS/MyGame -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=dev_abc123
```

### Multiple Properties

You can override multiple properties by using multiple `-ini:` arguments:

```bash
./MyGame \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=dev_abc123 \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:GameVersion=1.0.0 \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerLogLevel=3
```

### CI/CD Pipeline Example

In your CI/CD pipeline, you can configure different environments:

```yaml
# Development Environment
./MyGame \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=$DEV_API_KEY \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:GameVersion=$BUILD_VERSION \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerLogLevel=3

# Staging Environment  
./MyGame \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=$STAGING_API_KEY \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:GameVersion=$BUILD_VERSION \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerLogLevel=2

# Production Environment
./MyGame \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerGameKey=$PROD_API_KEY \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:GameVersion=$BUILD_VERSION \
  -ini:Game:[/Script/LootLockerSDK.LootLockerConfig]:LootLockerLogLevel=1
```

## Alternative: Using INI Files Directly

You can also override configuration by providing a custom INI file:

1. Create a custom INI file (e.g., `CustomGame.ini`):
```ini
[/Script/LootLockerSDK.LootLockerConfig]
LootLockerGameKey=dev_abc123
GameVersion=1.0.0
LootLockerLogLevel=3
```

2. Use it with the `-ini:` parameter:
```bash
./MyGame -ini:Game=CustomGame.ini
```

## Implementation Details

- Unreal Engine's config system automatically handles loading and applying command line overrides
- Overrides are applied before `PostInitProperties()` is called
- Values are loaded from INI files, then command line overrides are applied on top
- Command line overrides are not persisted back to INI files
- This follows Epic's recommended approach as documented in the [official Unreal Engine documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/configuration-files-in-unreal-engine)

## Advantages of Using Unreal's Built-in System

- **Epic-recommended approach**: Follows official Unreal Engine best practices
- **Zero maintenance**: Built-in and tested by Epic Games
- **Consistent behavior**: Works the same way as all other Unreal Engine config properties
- **Automatic support**: Any new config properties automatically get command line override support
- **Well-documented**: Part of Unreal Engine's standard documentation

## Notes

- Command line arguments override values from config files (Game.ini, DefaultGame.ini)
- Overrides are applied at runtime and are not persisted
- Invalid values will be handled according to property validation rules
- Property names are case-sensitive in the `-ini:` syntax
- For enum values like `LootLockerLogLevel`, use the numeric value (0-3)
