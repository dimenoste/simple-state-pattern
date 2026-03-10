# simple-state-pattern

A simple example to introduce the reader to the state pattern in C. 
The simplest example is a door.
A state machine is a machine that responds to the same input differently, depending on its current state.
For example, closing a door has two very different effects whether or not it is closed.
Indeed, if the door is closed, closing it does not do anything. If the door is opened, closing it make it closed. While sounding really trivial in this example, it can get really complex quickly. That is why we use a state pattern, a programming methodology to organize the code to be modular and keep it clear.


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