#pragma once

#include <ecs/types.h>

namespace sop {
namespace ecs {

/**
 * @brief 实体类型
 *
 * 唯一标识游戏世界中的对象。
 * Entity 仅包含 EntityId，不包含任何数据或行为。
 *
 * 线程安全：Entity 本身是值类型，线程安全。
 * 复杂度：所有操作均为 O(1)。
 */
class Entity {
public:
    /**
     * @brief 默认构造函数
     *
     * 创建一个无效的实体（id = INVALID_ENTITY_ID）。
     */
    constexpr Entity() : m_id(INVALID_ENTITY_ID) {}

    /**
     * @brief 构造函数
     *
     * @param id 实体 ID
     */
    explicit constexpr Entity(EntityId id) : m_id(id) {}

    /**
     * @brief 检查实体是否有效
     *
     * @return true 表示实体有效，false 表示实体无效
     */
    constexpr bool is_valid() const {
        return m_id != INVALID_ENTITY_ID;
    }

    /**
     * @brief 获取实体的 ID
     *
     * @return 实体 ID
     */
    constexpr EntityId id() const {
        return m_id;
    }

    /**
     * @brief 相等比较
     *
     * @param other 其他实体
     * @return true 表示相等，false 表示不相等
     */
    constexpr bool operator==(const Entity& other) const {
        return m_id == other.m_id;
    }

    /**
     * @brief 不等比较
     *
     * @param other 其他实体
     * @return true 表示不相等，false 表示相等
     */
    constexpr bool operator!=(const Entity& other) const {
        return !(*this == other);
    }

private:
    EntityId m_id;  ///< 实体 ID
};

} // namespace ecs
} // namespace sop