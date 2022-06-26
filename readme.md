# Mono Test Project (x64)
***

### Description
___
Project made to learn how to make C# scripts for C++ engines using Mono.
`projects/UnigineTest1/source/node.h` declares class `Node` which is used as base class (`assets/Node.cs`) for C# classes (base component as it is _MonoBehaviour_ in Unity)
`assets/MyNode.cs` declares class `MyNode` which is used as engine object (as if _class MyNode : Monobehaviour {}_ in Unity was created)
`config.json` stores paths for Mono and engine assets and components
- _monoAssemblyDir_ and _monoConfigDir_ have to point to Mono installation libraries

### Execution
___
1. Assets compilation (C# components)
2. C++ objects creation from component dll
3. C# objects creation from component dll

### Future ideas
- Create `Params` class to pass arguments into components methods execution (it is hardcoded for now)
- Add reflection pass to determine inheritance in C# components
- Find ways to optimise Mono methods execution