diag_log "We can run stuff right in VS Code! \o/";

#define square(b) b*b

_a = 3;
_b = square(_a);
diag_log format ["Let's compute a square of %1", _a];
diag_log format ["Square: %1", _b];