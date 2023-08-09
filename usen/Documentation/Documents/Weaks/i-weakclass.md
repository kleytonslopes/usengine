# Usen Kyrnness Engine :: IWeakClass
---

[![BuildVersion](https://raw.githubusercontent.com/kleytonslopes/md-asset/main/icons/build/vbuild_dev.svg)](https://github.com/kleytonslopes/md-asset/blob/main/icons/build/vbuild_dev.svg)

## IWeakClass


**Base Class:** N/A

**Include:** ```#include "Weaks/WeakClass.hpp"```

### Constructors
|          | **Access** | **Name**     | **Observation** |
| --       | --         | --           | --              |
| explicit | public     | IWeakClass() | --              |

### Properties
|    | **Type**      | **Access** | **Name**       | **Observation**     |
| -- | --            | --         | --             | --                  |
|    | FString       | protected  | Id             | GUID String         |
|    | FString       | protected  | Identity       | Class name identity |
|    | bool          | protected  | bIsInitialized | Used to verify if object is initialized. |

### Methods
|          | **Type**      | **Access** | **Name**                             | **Observation**   |
| --       | --            | --         | --                                   | --                |
| virtual  | void          | public     | Create()                             | pure function     |
| virtual  | void          | public     | PostCreate()                         | pure function     |
| virtual  | void          | public     | Initialize()                         | pure function     |
| virtual  | void          | public     | PostInitialize()                     | pure function     |
| virtual  | void          | public     | Destroy()                            | pure function     |
| virtual  | void          | public     | PostDestroy()                        | pure function     |
|          | const FString | public     | GetId()                              | Get class GUID Id |
|          | const FString | public     | GetIdentity()                        | Get class Identity "ClassName" |
|          | inline void   | protected  | SetIdentity(const FString& identity) | Set class Identity "ClassName" |