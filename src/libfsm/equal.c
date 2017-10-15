/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>

#include <adt/set.h>

#include <fsm/fsm.h>
#include <fsm/bool.h>

#include "internal.h"
#include "walk2.h"

struct fsm *
subtract(const struct fsm *a, const struct fsm *b)
{
	struct fsm *q;
	struct fsm *x, *y;

	assert(a != NULL);
	assert(b != NULL);

	x = fsm_clone(a);
	if (x == NULL) {
		return NULL;
	}

	y = fsm_clone(b);
	if (y == NULL) {
		fsm_free(x);
		return NULL;
	}

	/* see fsm_subtract() */
	q = fsm_walk2(x, y, FSM_WALK2_ONLYA | FSM_WALK2_BOTH, FSM_WALK2_ONLYA);

	fsm_free(x);
	fsm_free(y);

	return q;
}

static int
subsetof(const struct fsm *a, const struct fsm *b)
{
	struct fsm *q;
	int r;

	assert(a != NULL);
	assert(b != NULL);

	q = subtract(b, a);
	if (q == NULL) {
		return -1;
	}

	r = fsm_empty(q);

	fsm_free(q);

	if (r == -1) {
		return -1;
	}

	return r;
}

int
fsm_equal(const struct fsm *a, const struct fsm *b)
{
	assert(a != NULL);
	assert(b != NULL);

	if (a->opt != b->opt) {
		errno = EINVAL;
		return -1;
	}

	if (fsm_empty(a) && fsm_empty(b)) {
		return 1;
	}

	/*
	 * The subset operation is not commutative; sets are equal
	 * when one set is a subset of the other and vice versa.
	 * This is equivalent finding that (a \ b) \u (b \ a) is empty.
	 */

	return subsetof(a, b) && subsetof(b, a);
}

