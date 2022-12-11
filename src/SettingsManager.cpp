#include <SettingsManager.hpp>
#include <IniParser/Ini.hpp>

#define REGISTER_STRING_SETTING(member_var, section_name, key)          \
try                                                                     \
{                                                                       \
    (member_var) = parser.get_string(section_name, STR(#key));          \
}                                                                       \
catch (std::exception&) {}

#define REGISTER_INT64_SETTING(member_var, section_name, key)           \
try                                                                     \
{                                                                       \
    (member_var) = parser.get_int64(section_name, STR(#key));           \
}                                                                       \
catch (std::exception&) {}

#define REGISTER_BOOL_SETTING(member_var, section_name, key)            \
try                                                                     \
{                                                                       \
    (member_var) = parser.get_bool(section_name, STR(#key));            \
}                                                                       \
catch (std::exception&) {}

namespace RC
{
    auto SettingsManager::deserialize(std::filesystem::path& file_name) -> void
    {
        auto file = File::open(file_name, File::OpenFor::Reading, File::OverwriteExistingFile::No, File::CreateIfNonExistent::Yes);
        Ini::Parser parser;
        parser.parse(file);
        file.close();

        constexpr static File::CharType section_overrides[] = STR("Overrides");
        REGISTER_STRING_SETTING(Overrides.ModsFolderPath, section_overrides, ModsFolderPath)

        constexpr static File::CharType section_general[] = STR("General");
        REGISTER_BOOL_SETTING(General.EnableHotReloadSystem, section_general, EnableHotReloadSystem)
        REGISTER_BOOL_SETTING(General.InvalidateCacheIfDLLDiffers, section_general, InvalidateCacheIfDLLDiffers)
        REGISTER_BOOL_SETTING(General.EnableDebugKeyBindings, section_general, EnableDebugKeyBindings)
        REGISTER_INT64_SETTING(General.MaxScanAttemptsNormal, section_general, MaxScanAttemptsNormal)
        REGISTER_INT64_SETTING(General.MaxScanAttemptsModular, section_general, MaxScanAttemptsModular)
        REGISTER_BOOL_SETTING(General.bUseUObjectArrayCache, section_general, UseUObjectArrayCache)

        constexpr static File::CharType section_engine_version_override[] = STR("EngineVersionOverride");
        REGISTER_INT64_SETTING(EngineVersionOverride.MajorVersion, section_engine_version_override, MajorVersion)
        REGISTER_INT64_SETTING(EngineVersionOverride.MinorVersion, section_engine_version_override, MinorVersion)

        constexpr static File::CharType section_object_dumper[] = STR("ObjectDumper");
        REGISTER_BOOL_SETTING(ObjectDumper.LoadAllAssetsBeforeDumpingObjects, section_object_dumper, LoadAllAssetsBeforeDumpingObjects)

        constexpr static File::CharType section_cxx_header_generator[] = STR("CXXHeaderGenerator");
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.DumpOffsetsAndSizes, section_cxx_header_generator, DumpOffsetsAndSizes)
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.KeepMemoryLayout, section_cxx_header_generator, KeepMemoryLayout)
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders, section_cxx_header_generator, LoadAllAssetsBeforeGeneratingCXXHeaders)

        constexpr static File::CharType section_uht_header_generator[] = STR("UHTHeaderGenerator");
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.IgnoreAllCoreEngineModules, section_uht_header_generator, IgnoreAllCoreEngineModules)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.IgnoreEngineAndCoreUObject, section_uht_header_generator, IgnoreEngineAndCoreUObject)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeAllFunctionsBlueprintCallable, section_uht_header_generator, MakeAllFunctionsBlueprintCallable)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeAllPropertyBlueprintsReadWrite, section_uht_header_generator, MakeAllPropertyBlueprintsReadWrite)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeEnumClassesBlueprintType, section_uht_header_generator, MakeEnumClassesBlueprintType)

        constexpr static File::CharType section_debug[] = STR("Debug");
        REGISTER_BOOL_SETTING(Debug.SimpleConsoleEnabled, section_debug, ConsoleEnabled)
        REGISTER_BOOL_SETTING(Debug.DebugConsoleEnabled , section_debug, GuiConsoleEnabled)
        REGISTER_BOOL_SETTING(Debug.DebugConsoleVisible, section_debug, GuiConsoleVisible)

        constexpr static File::CharType section_threads[] = STR("Threads");
        REGISTER_INT64_SETTING(Threads.SigScannerNumThreads, section_threads, SigScannerNumThreads)
        REGISTER_INT64_SETTING(Threads.SigScannerMultithreadingModuleSizeThreshold, section_threads, SigScannerMultithreadingModuleSizeThreshold)

        constexpr static File::CharType section_memory[] = STR("Memory");
        REGISTER_INT64_SETTING(Memory.MaxMemoryUsageDuringAssetLoading, section_memory, MaxMemoryUsageDuringAssetLoading)
    }
}
