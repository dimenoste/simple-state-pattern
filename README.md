# simple-state-pattern

# State Pattern (from the code)

## Core Idea

- The program implements a **finite state machine** using the **State Pattern**.
- The **context does not decide behavior**.
- The context **delegates events to the current state** through function pointers.
- Each state **implements the behavior for the same events differently**.

---

# Components

## Context

```
contextState
```

Responsibilities:

- stores the **current state interface**
- stores the **state name**
- stores **state data** (`nber_opening`)
- **delegates events to the current state**

Example:

```
mystate.interface->handler_open(&mystate);
```

---

## State Interface

Defines the operations every state must implement.

```
struct s_interface
{
    void (*handler_open)(contextState *);
    void (*handler_close)(contextState *);
};
```

Events supported:

- `open`
- `close`

---

## Concrete States

Two states exist:

```
OpenedState
ClosedState
```

Each state provides its own handlers:

```
OpenedState:
    handler_open  -> OpenWhenOpened
    handler_close -> CloseWhenOpened

ClosedState:
    handler_open  -> OpenWhenClosed
    handler_close -> CloseWhenClosed
```

Same event → different behavior depending on the state.

---

## Transitions

State changes are implemented through helper functions.

```
toOpened()
```

Effects:

- switch interface → `OpenedState`
- update state name
- increment `nber_opening`

```
toClosed()
```

Effects:

- switch interface → `ClosedState`
- update state name

---

# State Behavior

## CLOSED

```
open  -> OPENED
close -> CLOSED
```

Handlers:

```
OpenWhenClosed()  -> toOpened()
CloseWhenClosed() -> toClosed()
```

---

## OPENED

```
open  -> OPENED
close -> CLOSED
```

Handlers:

```
OpenWhenOpened()  -> toOpened()
CloseWhenOpened() -> toClosed()
```

---

# Execution Flow

Event dispatch:

```
User event
    ↓
Context
    ↓
Current State Interface
    ↓
State Handler
    ↓
Optional transition
```

Example:

```
mystate.interface->handler_open(&mystate);
```

The function executed depends on the **current state**.

---

# Key Properties

- No `if` or `switch` on state.
- Behavior is **encapsulated inside states**.
- Context only **stores state and delegates events**.
- New states can be added **without modifying the context**.