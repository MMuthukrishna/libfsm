/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

int
class_notvspace_fsm(struct fsm *fsm, fsm_state_t x, fsm_state_t y)
{
	fsm_state_t s[2];
	size_t i;

	for (i = 0; i < 2; i++) {
		if (i == 0) {
			s[0] = x;
			continue;
		}

		if (i == 1) {
			s[1] = y;
			continue;
		}

		if (!fsm_addstate(fsm, &s[i])) {
			return 0;
		}
	}

	for (i = 0x00; i <= 0x09; i++) {
		if (!fsm_addedge_literal(fsm, s[0], s[1], i)) { return 0; }
	}
	for (i = 0x0e; i <= 0xff; i++) {
		if (!fsm_addedge_literal(fsm, s[0], s[1], i)) { return 0; }
	}

	return 1;
}
