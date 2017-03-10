#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
#include <pbconsole.h>

/* custom constant event type ids*/
enum {
	KeyInputEventTypeId = 47578
};

/* event handler functions prototypes */
void KeyInputHandler_update(EventHandler * self, Event * event);
void KeyInputListener_update(EventHandler * self, Event * event);

int main(void) {
	// startup event system
	EventSystem_init();

	// add event handlers
	EventSystem_addHandler(EventHandler_new(NULL, NULL, KeyInputHandler_update));
	EventSystem_addHandler(EventHandler_new(NULL, NULL, KeyInputListener_update));

	// start infinite event loop
	EventSystem_loop();
	// cleanup event system
	EventSystem_deinit();
	return 0;
}

/* event handlers functions implementations */

void KeyInputHandler_update(EventHandler * self, Event * event) {
	if (conIsKeyDown()) {  // non-blocking key input check
		char * keyCode = malloc(sizeof(char));
		*keyCode = getchar();
		if (*keyCode == 27) {  // Escape key
			EventSystem_raiseEvent(Event_new(self, ExitEventTypeId, keyCode, free));	
		} else {
			EventSystem_raiseEvent(Event_new(self, KeyInputEventTypeId, keyCode, free));
		}
	}
}

void KeyInputListener_update(EventHandler * self, Event * event) {
	switch(event->type) {
		case StartEventTypeId: {
			puts("Press [Esc] to exit");
			break;
		}
		case KeyInputEventTypeId: {
			char keyCode = *(char *)event->data;
			printf("\nNew Event >> Key `%c` (%i) was pressed", keyCode, keyCode);
			break;
		}
	}
}