/* $Id$ */

#include <assert.h>
#include <stddef.h>
#include <ctype.h>

#include <adt/set.h>

#include <fsm/fsm.h>

#include "internal.h"

int
fsm_desensitise(struct fsm *fsm)
{
	struct fsm_state *s, *e;
	int i;

	assert(fsm != NULL);

	for (s = fsm->sl; s != NULL; s = s->next) {
		for (i = 0; i <= FSM_EDGE_MAX; i++) {
			struct set_iter it;
			struct set *l;
			unsigned char u;

			if (!islower((unsigned char) i)) {
				continue;
			}

			u = toupper((unsigned char) i);

			l = s->edges[i].sl;

			for (e = set_first(s->edges[u].sl, &it); e != NULL; e = set_next(&it)) {
				if (!set_add(&s->edges[i].sl, e)) {
					return 0;
				}
			}

			/* items pushed before l have already been done */
			for (e = set_first(l, &it); e != NULL; e = set_next(&it)) {
				if (!set_add(&s->edges[u].sl, e)) {
					return 0;
				}
			}
		}
	}

	return 1;
}

