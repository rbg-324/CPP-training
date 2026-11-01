# 实验三过程记录

## 第一阶段 解耦循环依赖

将四个指令类移至 Command.hpp，把位姿、加速状态及基础操作抽到 PoseHandler.hpp/.cpp。ExecutorImpl 持有 PoseHandler，指令类只接收 PoseHandler 引用。Command.hpp 无须包含 ExecutorImpl.hpp，依赖关系变为 ExecutorImpl → Command → PoseHandler。

验证：重新配置 MinGW Makefiles 并构建，运行原有 18 项测试。截图及实际结果随阶段保存。

## 第二阶段 表驱动与方向状态抽象

用 unordered_map<char, unique_ptr<ICommand>> 建立 M/L/R/F 到指令对象的映射，Execute 的循环统一执行查表和调用。将朝向按 N/E/S/W 排列，以方向步长表执行前进，以模 4 运算完成转向，保留无效朝向不改变位姿的处理。

验证：原有 18 项测试保持通过。
