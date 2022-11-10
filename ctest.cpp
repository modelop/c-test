// modelop.schema.0: input_schema.avsc
// modelop.schema.1: output_schema.avsc

#include "fastscore.h"
#include <jansson.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// modelop.init
void begin()
{
    printf("In Begin()\n");
}

// modelop.score
void action(fastscore_value_t v, int slot, int seqno)
{
    printf("In action got value fmt %d slot %d seqno %d\n", v.fmt, slot, seqno);
    int i;
    json_t *a = v.js;
    json_t *b = json_array();
    size_t count = json_array_size(a);
    printf("The input array has %d elements\n", count);
    for (i = 0; i < count; i++)
    {
        json_t *bar = json_array_get(a, i);
        json_t *foo = json_object_get(bar, "field_1");
        double v = json_number_value(foo);
        v *= v;
        json_t *response = json_object();
        json_object_set(response, "square_field_1", json_real(v));
        json_object_set(response, "field_5", json_string("test"));
        json_array_append_new(b, response);
        printf("Just appended square %lf to array, current length: %d\n", v, json_array_size(b));
    }
    printf("Before fastscore_emit\n");
    fastscore_emit((fastscore_value_t){
                       .fmt = FASTSCORE_FMT_JSON,
                       .js = b,
                   },
                   1);
    printf("After fastscore_emit, returning from action()\n");
}

void end1()
{
    printf("End1()\n");
}
