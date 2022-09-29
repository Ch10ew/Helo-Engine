#ifndef HE_ASSET_MANAGER_BASE_HPP
#define HE_ASSET_MANAGER_BASE_HPP

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <string>

namespace he
{
    /**
     * @brief Base abstract class for asset managers. When making a new custom asset manager, inherit from this class.
     *
     * @tparam T Asset type
     */
    template <typename T>
    class AssetManagerBase
    {
    public:
        /**
         * @brief Load an asset.
         */
        virtual void Load(const std::string&, const std::string&) {}

        /**
         * @brief Load an asset. Variant for shader (1).
         */
        virtual void Load(const std::string&, const std::string&, sf::Shader::Type) {}

        /**
         * @brief Load an asset. Variant for shader (2).
         */
        virtual void Load(const std::string&, const std::string&, const std::string&) {}

        /**
         * @brief Load an asset. Variant for shader (3).
         */
        virtual void Load(const std::string&, const std::string&, const std::string&, const std::string&) {}

        /**
         * @brief Unload an asset.
         */
        virtual void Unload(const std::string&) = 0;

        /**
         * @brief Get a loaded asset.
         *
         * @return T& Reference to asset
         */
        virtual T& Get(const std::string&) = 0;

        /**
         * @brief Get a loaded asset.
         *
         * @return T& Reference to asset
         */
        virtual const T& Get(const std::string&) const = 0;

    protected:
        /**
         * @brief Loaded assets map.
         */
        std::map<std::string, std::unique_ptr<T>> _assets;
    };
} // namespace he

#endif // HE_ASSET_MANAGER_BASE_HPP
