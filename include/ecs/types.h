#pragma once

#include <cstdint>
#include <string>

namespace sop {
namespace ecs {

/**
 * @brief 实体标识符类型
 *
 * 唯一标识游戏世界中的实体。
 * 取值范围：1 到 UINT64_MAX（0 保留为无效实体 ID）。
 * 线程安全：EntityId 本身是值类型，线程安全。
 */
using EntityId = uint64_t;

/**
 * @brief 组件类型标识符类型
 *
 * 唯一标识组件类型。
 * 取值范围：1 到 UINT32_MAX（0 保留为无效组件类型 ID）。
 * 线程安全：ComponentTypeId 本身是值类型，线程安全。
 */
using ComponentTypeId = uint32_t;

/**
 * @brief 系统标识符类型
 *
 * 唯一标识系统实例。
 * 取值范围：1 到 UINT32_MAX（0 保留为无效系统 ID）。
 * 线程安全：SystemId 本身是值类型，线程安全。
 */
using SystemId = uint32_t;

/**
 * @brief 事件订阅标识符类型
 *
 * 唯一标识事件订阅。
 * 取值范围：1 到 UINT32_MAX（0 保留为无效订阅 ID）。
 * 线程安全：SubscriptionId 本身是值类型，线程安全。
 */
using SubscriptionId = uint32_t;

/**
 * @brief 执行阶段枚举
 *
 * 标识系统执行的阶段。
 * 线程安全：Phase 本身是值类型，线程安全。
 */
enum class Phase : uint8_t {
    Input = 0,      ///< 输入阶段，处理用户输入
    Simulate = 1,   ///< 模拟阶段，模拟游戏逻辑
    Resolve = 2,    ///< 解决阶段，解决游戏状态
    Render = 3      ///< 渲染阶段，渲染游戏画面（可选）
};

/**
 * @brief 操作结果枚举
 *
 * 表示操作结果（成功或失败）。
 * 线程安全：Result 本身是值类型，线程安全。
 */
enum class Result : uint8_t {
    Success = 0,                ///< 操作成功
    InvalidEntity = 1,          ///< 无效实体 ID
    InvalidComponentType = 2,   ///< 无效组件类型 ID
    InvalidSystemId = 3,        ///< 无效系统 ID
    InvalidSubscriptionId = 4,  ///< 无效订阅 ID
    ComponentNotFound = 5,      ///< 组件未找到
    SystemNotFound = 6,         ///< 系统未找到
    DuplicateComponent = 7,     ///< 重复添加组件
    DuplicateSystem = 8,        ///< 重复注册系统
    InternalError = 9           ///< 内部错误
};

/**
 * @brief 错误详情类
 *
 * 表示错误详情，包含错误码和错误信息字符串。
 * 线程安全：Error 本身是值类型，线程安全。
 */
class Error {
public:
    /**
     * @brief 默认构造函数
     *
     * 创建一个成功的错误对象（code = Result::Success，message = ""）。
     */
    Error() : code_(Result::Success), message_("") {}

    /**
     * @brief 构造函数
     *
     * @param code 错误码
     * @param message 错误信息字符串
     */
    Error(Result code, const std::string& message)
        : code_(code), message_(message) {}

    /**
     * @brief 获取错误码
     *
     * @return 错误码
     */
    Result code() const { return code_; }

    /**
     * @brief 获取错误信息
     *
     * @return 错误信息字符串
     */
    const std::string& message() const { return message_; }

    /**
     * @brief 检查是否成功
     *
     * @return true 表示成功，false 表示失败
     */
    bool is_success() const { return code_ == Result::Success; }

    /**
     * @brief 相等比较
     *
     * @param other 其他错误对象
     * @return true 表示相等，false 表示不相等
     */
    bool operator==(const Error& other) const {
        return code_ == other.code_ && message_ == other.message_;
    }

    /**
     * @brief 不等比较
     *
     * @param other 其他错误对象
     * @return true 表示不相等，false 表示相等
     */
    bool operator!=(const Error& other) const {
        return !(*this == other);
    }

private:
    Result code_;          ///< 错误码
    std::string message_;  ///< 错误信息字符串
};

/**
 * @brief 常量：无效实体 ID
 */
constexpr EntityId INVALID_ENTITY_ID = 0;

/**
 * @brief 常量：无效组件类型 ID
 */
constexpr ComponentTypeId INVALID_COMPONENT_TYPE_ID = 0;

/**
 * @brief 常量：无效系统 ID
 */
constexpr SystemId INVALID_SYSTEM_ID = 0;

/**
 * @brief 常量：无效订阅 ID
 */
constexpr SubscriptionId INVALID_SUBSCRIPTION_ID = 0;

} // namespace ecs
} // namespace sop