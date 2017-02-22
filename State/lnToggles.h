typedef struct {
	bool val,
		valLast,
		delta,
		rise,
		fall;
} Toggle;

bool upTog(Toggle* tog, bool val) {
	tog->valLast = tog->val;
	tog->val = val;
	tog->delta = ((tog->val && !tog->valLast) || (!tog->val && tog->valLast)); //I don't like bad type warnings, so this is a manual xor
	tog->rise = tog->delta && tog->val;
	tog->fall = tog->delta && tog->valLast;
	return tog->val;
}

bool togVal(Toggle* tog) {
	return tog->val;
}

bool togValLast(Toggle* tog) {
	return tog->valLast;
}

bool togDelta(Toggle* tog) {
	return tog->delta;
}

bool togRising(Toggle* tog) {
	return tog->rise;
}

bool falling(Toggle* tog) {
	return tog->fall;
}
