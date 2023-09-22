#include "Int.h"
#include <stdint.h>

void *new_Int(char *string) {
    Int *obj = malloc(sizeof(Int));
    if (obj) {
        obj->impl = malloc(sizeof(GenericTraits));
        obj->impl->new = new_Int;
        obj->impl->dump = dump_Int;
        obj->impl->cmp = cmp_Int;
        obj->impl->drop = drop_Int;
        obj->i = atoi(string);
    }
    return obj;
}

void dump_Int(void *self, FILE *fp) {
    if (self) {
        Int *obj = (Int *)self;
        fprintf(fp, "0x%x\n", obj->i);
    }
}

int cmp_Int(void *self, void *other) {
    if (self && other) {
        Int *obj1 = (Int *)self;
        Int *obj2 = (Int *)other;
        if (obj1->i < obj2->i){
            //printf(" %d < %d returning -1\n", obj1->i, obj2->i);
            return -1;
        }

        else if (obj1->i > obj2->i){
            //printf(" %d > %d returning 1\n", obj1->i, obj2->i);
            return 1;

        }
        else
            return 0;

    }
    return 0;
}

void drop_Int(void *self) {
    if (self) {
        Int *obj = (Int *)self;
        free(obj->impl);
        free(obj);
    }
}

void __attribute__((constructor)) register_Int() {
    add_ctor_dtor("Int", new_Int, drop_Int);
}