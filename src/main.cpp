#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_random.h>
#include <bn_vector.h>
#include <bn_log.h>

#include "bn_sprite_items_dot.h"

static constexpr int HALF_SCREEN_WIDTH = bn::display::width() / 2;

static constexpr bn::fixed MIN_X = -HALF_SCREEN_WIDTH;
static constexpr bn::fixed MAX_X = HALF_SCREEN_WIDTH;

static constexpr bn::fixed BASE_SPEED = 2;

static constexpr int MAX_BOUNCERS = 20;


int main() {
    bn::core::init();

    bn::vector<bn::sprite_ptr, MAX_BOUNCERS> sprites = {};
    bn::vector<bn::fixed, MAX_BOUNCERS> speeds = {};

    while(true) {

        if(bn::keypad::a_pressed()) {
            if(sprites.size() < sprites.max_size()) {
                sprites.push_back(bn::sprite_items::dot.create_sprite());
                speeds.push_back(BASE_SPEED);
            }
        }

        if(bn::keypad::b_pressed()) {
            bn::fixed x_sum = 0;
            for(bn::sprite_ptr sprite : sprites) {
                x_sum += sprite.x();
            }
            bn::fixed x_average= x_sum;
            if(sprites.size() > 0) {
                x_average /= sprites.size();
            }
            BN_LOG("Average x: ", x_average);
        }

        for(int i = 0; i < sprites.size(); i++) {
            bn::sprite_ptr sprite = sprites[i];

            bn::fixed x = sprite.x();

            x += speeds[i];

            if(x > MAX_X) {
                x = MAX_X;
                speeds[i] *=-1;
            }
            if(x < MIN_X) {
                x = MIN_X;
                speeds[i] *= -1;
            }

            sprite.set_x(x);
        }

        bn::core::update();
    }
}