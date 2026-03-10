#include <stdio.h>

// 1) Context
typedef struct s_interface	stateInterface;
typedef struct s_ctx
{
	stateInterface			*interface;
	char					*name_state;
	int						nber_opening;
}							contextState;

// 2) State Interface
struct						s_interface
{
	void					(*handler_open)(contextState *);
	void					(*handler_close)(contextState *);
};

// 3) Concrete States
void						OpenWhenClosed(contextState *currState);
void						CloseWhenClosed(contextState *currState);
void						OpenWhenOpened(contextState *currState);
void						CloseWhenOpened(contextState *currState);

stateInterface				OpenedState = {.handler_open = &OpenWhenOpened,
					.handler_close = &CloseWhenOpened};
stateInterface				ClosedState = {&OpenWhenClosed, &CloseWhenClosed};


// transitions
void	toOpened(contextState *currState)
{
	currState->interface = &OpenedState;
	currState->name_state = "Opened";
	currState->nber_opening += 1;
}

void	toClosed(contextState *currState)
{
	currState->interface = &ClosedState;
	currState->name_state = "Closed";
}

// fromClosedToClosed(contextState *currState)
// {
// 	currState->state = ClosedState;
// }

// fromOpenedToOpened(contextState *currState)
// {
// 	currState->state = OpenedState;
// }
// On Closed
void	OpenWhenClosed(contextState *currState)
{
	printf("============================================\n");
	printf("current state is : %s\n", currState->name_state);
	toOpened(currState);
	printf("current state is : %s\n", currState->name_state);
	printf("============================================\n");
}

void	CloseWhenClosed(contextState *currState)
{
	printf("============================================\n");
	printf("current state is : %s\n", currState->name_state);
	toClosed(currState);
	printf("current state is : %s\n", currState->name_state);
	printf("============================================\n");
}

// On Opened
void	OpenWhenOpened(contextState *currState)
{
	printf("============================================\n");
	printf("current state is : %s\n", currState->name_state);
	toOpened(currState);
	printf("current state is : %s\n", currState->name_state);
	printf("============================================\n");
}

void	CloseWhenOpened(contextState *currState)
{
	printf("============================================\n");
	printf("current state is : %s\n", currState->name_state);
	toClosed(currState);
	printf("current state is : %s\n", currState->name_state);
	printf("============================================\n");
}

int	main(void)
{
	contextState	mystate;

	toOpened(&mystate);
	// The user interacts:
	mystate.interface->handler_open(&mystate);


	mystate.interface->handler_open(&mystate);

	
	mystate.interface->handler_close(&mystate);
	// mystate.interface->handler_close(&mystate);
	// mystate.interface->handler_open(&mystate);
	// mystate.interface->handler_close(&mystate);
	return (0);
}
