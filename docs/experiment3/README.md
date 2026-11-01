# 实验三

四个任务依次完成：状态抽离解耦、表驱动与方向状态抽象、函数式调用与 operator() 重载、B 倒车指令。

| 阶段 | 分支 | 关键代码提交 | 测试结果 |
| --- | --- | --- | --- |
| 解耦循环依赖 | exp3-decouple | b3ae079 | 原有 18 项通过 |
| 表驱动和方向状态简化 | exp3-table | a2812ba | 原有 18 项通过 |
| lambda 中间版本 | exp3-functional | f41c738 | 原有 18 项通过 |
| operator() 函数对象 | exp3-functional | 0f8b4d6 | 原有 18 项通过 |
| 先写 B 测试 | exp3-reverse-tests | b1a7105 | 9 项中 8 项未通过、1 项通过 |
| B 与 BF 实现 | exp3-final | 557dfe6 | 全部 27 项通过，CTest 通过 |

## 构建与运行

在 PowerShell 中执行：

```powershell
Set-Location D:\workspace\cpp-training
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\tests\training_main.exe --gtest_brief=1
ctest --test-dir build --output-on-failure
```

单独运行新增倒车用例：

```powershell
.\build\tests\training_main.exe '--gtest_filter=Reverse*'
```

截图位于 screenshots，共 8 张。代码图来自各阶段的 VS Code 编辑器；测试图来自实际运行。08-final-27-tests.png 摘出真实输出中的倒车说明和完整 27 项汇总，完整输出见 04-final-27.log。

实验报告为 实验3报告_标准模板版.docx，正文四号宋体，保留标准模板封面、栏目、姓名学号及评分签字空栏。
