# Usen Kyrnness Engine :: UApplication
---

[![BuildVersion](https://raw.githubusercontent.com/kleytonslopes/md-asset/main/icons/build/vbuild_dev.svg)](https://github.com/kleytonslopes/md-asset/blob/main/icons/build/vbuild_dev.svg)

## UApplication


**Base Class:** [IWeakClass](../Weaks/i-weakclass.md)

**Include:** ```#include "Runtime/Application.hpp"```

### Friends

- BClass

### Constructors
|          | **Access** | **Name**     | **Observation** |
| --       | --         | --           | --              |
| explicit | public     | UApplication() | --              |

### Properties
|    | **Type**                       | **Access** | **Name**            | **Observation**                  |
| -- | --                             | --         | --                  | --                               |
|    | FString                        | public     | OnUpdateEvent       | Update event called every Tick.  |
|    | TClassOf\<UGameInstance\>      | protected  | DefaultGameInstance | Default class of GameInstance    |
|    | TClassOf\<BRenderer\>          | protected  | DefaultRenderer     | Default class of Renderer System |
|    | USharedPtr\<UWindow\>          | private    | Window              | Window instance.                 |
|    | USharedPtr\<UGameInstance\>    | private    | GameInstance        | Game instance.                   |
|    | USharedPtr\<BRenderer\>        | private    | GameInstance        | Renderer instance.               |
|    | USharedPtr\<UScene\>           | private    | Scene               | Current Scene instance.          |
|    | USharedPtr\<UInputManagement\> | private    | InputManagement     | Input Management instance.       |
|    | UController*                   | private    | Controller          | Pointer to current Controller.   |

### Methods
|          | **Type** | **Access** | **Name**                                               | **Observation**                |
| --       | --       | --         | --                                                     | --                             |
| virtual  | void     | public     | Create()                                               | pure function                  |
| virtual  | void     | public     | PostCreate()                                           | pure function                  |
| virtual  | void     | public     | Initialize()                                           | pure function                  |
| virtual  | void     | public     | PostInitialize()                                       | pure function                  |
| virtual  | void     | public     | Destroy()                                              | pure function                  |
| virtual  | void     | public     | PostDestroy()                                          | pure function                  |
|          | T*       | public     | GetRenderer\<T\>()                                     | Get Custom Renderer.           |
| virtual  | void     | protected  | CreateWindow()                                         |                                |
| virtual  | void     | protected  | CreateGameInstance()                                   |                                |
| virtual  | void     | protected  | CreateRenderer()                                       |                                |
| virtual  | void     | protected  | CreateInputManagement()                                |                                |
| virtual  | void     | protected  | CreateScene()                                          |                                |
| virtual  | void     | protected  | CreateController()                                     |                                |
| virtual  | void     | private    | Loop()                                                 |                                |
| virtual  | void     | private    | CalculeDeltaTime(FTime& currentTime, float& deltaTime) |                                |