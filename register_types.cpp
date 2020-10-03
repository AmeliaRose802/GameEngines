#include "register_types.h"
#include "core/class_db.h"
#include "PongNode.h"

void register_ECSModule_types() {
	ClassDB::register_class<PongNode>();
}

void unregister_ECSModule_types() {
}
