#ifndef LAB_ENVIRONMENT_H
#define LAB_ENVIRONMENT_H

#include <filesystem>

namespace LabEnvironment
{
    std::filesystem::path getLabDirectory();

    bool initialize();

    bool isInsideLab(
        const std::filesystem::path& path
    );
}

#endif