/**
 * Do not build into wasm. Only for testing via cli
 *  clang -std=c99 -m32 math.c test.c -o test; ./test
 */
#include "math.h"
#include "wefx.h"
#include <stdio.h>

int main()
{
    /* {
        for (int d = 0; d <= 45; d++)
        {
            float r = to_radian(d);
            printf("%d, %f, %f, %f\n", d, r, cos(r), sin(r));
        }
    } */

    // Simple math tests
    {
        printf("---------------------------\n");
        printf("abs: %f\n", abs(10));
        printf("abs: %f\n", abs(-399));
        printf("abs: %f\n", abs(-123.456));
        printf("abs: %f\n", abs(-0.200025));
        printf("---------------------------\n");
        printf("flr: %f == 2\n", floor(2.4));
        printf("flr: %f == -3\n", floor(-2.4));
        printf("flr: %f == -1\n", floor(-0.49333));
        printf("---------------------------\n");
        printf("cel: %f == 3\n", ceil(2.4));
        printf("cel: %f == -2\n", ceil(-2.4));
        printf("cel: %f == 0\n", ceil(-0.49333));
        printf("---------------------------\n");
        printf("rnd: %f == 39894\n", round(39894.399));
        printf("rnd: %f == 39895\n", round(39894.622));
        printf("rnd: %f == -124\n", round(-123.63));
        printf("---------------------------\n");
        printf("2rad: %f\n", to_radian(30));
        printf("2deg: %f\n", to_degree(M_PI / 2));
    }

    // Simple sin, cos tests
    {
        printf("---------------------------\n");
        printf("sin(0) == %f\n", sin(0));
        printf("sin(1) == %f\n", sin(1));
        printf("cos(0) == %f\n", cos(0));
        printf("cos(1) == %f\n", cos(1));
        // The value of cos(0.314000) : 0.951106)
        printf("0.951106 == %f\n", cos(0.314000));
        // The value of sin(0.314000) : 0.308866)
        printf("0.308866 == %f\n", sin(0.314000));
    }

    // Simple square root test
    {
        printf("---------------------------\n");
        printf("sqrt(2) == %f\n", sqrt(2));
        printf("sqrt(3.14) == %f\n", sqrt(3.14));
    }

    // Simple rand tests
    {
        printf("---------------------------\n");
        srand(12345); // my luggage combination
        for (int d = 0; d < 10; d++)
        {
            printf("rand %d: == %d\n", d, rand());
        }
        printf("---------------------------\n");
        srand(54321);
        for (int d = 0; d < 10; d++)
        {
            printf("rand %d: == %d\n", d, rand());
        }
    }

    // Simple queue tests
    {
        printf("---------------------------\n");
        wefx_event_queue q;
        wefx_init_queue(&q);
        printf("head: %#010x; tail: %#010x (should be zero)\n", (unsigned int)q.head, (unsigned int)q.tail);

        wefx_event e0 = {
            .type = WEFX_CLICK,
            .button = WEFX_RIGHT,
            .timestamp = 123456,
            .x = 0,
            .y = 0,
        };

        wefx_enqueue(&q, &e0);
        printf("head: %#010x; tail: %#010x (should be equal)\n", (unsigned int)q.head, (unsigned int)q.tail);

        wefx_event e1 = {
            .type = WEFX_MOUSEMOVE,
            .timestamp = 123458,
            .x = 10,
            .y = 10,
        };

        wefx_enqueue(&q, &e1);
        printf("head: %#010x; tail: %#010x (should be different)\n", (unsigned int)q.head, (unsigned int)q.tail);
        printf("h: %d; t: %d (should be different)\n", q.head->event->type, q.tail->event->type);

        wefx_event *e9 = wefx_dequeue(&q);

        printf("head: %#010x; tail: %#010x (should be different)\n", (unsigned int)q.head, (unsigned int)q.tail);
        printf("h: %d; t: %d (should be the same now)\n", q.head->event->type, q.tail->event->type);
        printf("dequeued: %d\n", e9->type);
    }
}