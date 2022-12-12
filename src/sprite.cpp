#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>

#include "src/sprite.hpp"
#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/movement.hpp"
#include "src/sprite_sheet.hpp"
#include "src/capture_zone.hpp"

namespace cge {

    Sprite::Sprite() {}

	Sprite::Sprite(float x1, float y1, SDLInfo si1, SDLTextureInfo sti1, SDLTextureOptions sto1) {
		si = si1;
		sti = sti1;
		sto = sto1;
		x = x1;
		y = y1;
        name = "";
	}

	Sprite::Sprite(float x1, float y1, SDLInfo si1, std::string image_path, int width1, int height1) {
		si = si1;
		sti = create_texture(si, image_path);
		sto.width = width1;
		sto.height = height1;
		path = image_path;
		x = x1;
		y = y1;
		name = "Mario";
	}

	Sprite::Sprite(float x1, float y1, SDLInfo si1, Texture t1, int width1, int height1, float scrW, float scrH, Sound* s) {
		si = si1;
        texture = t1;
		sti = create_texture(si, texture.get_motion(1));
		sto.width = width1;
		sto.height = height1;
		path = t1.get_motion(1);
		x = x1;
		y = y1;
        box = Box(x, x+width1, y, y+height1);
        screenWidth = scrW;
        screenHeight = scrH;
		name = "Mario";
        v = Vector(0, 0);
        sound = s;
	}

    Sprite::Sprite(float x1, float y1, SDLInfo si1, SpriteSheet* ss, int width1, int height1, float scrW, float scrH, Sound* s, SpriteType spriteType) {
        si = si1;
        sheet = ss;
        sti = create_texture(si, ss->get_file());
        sto.width = width1;
        sto.height = height1;
        path = ss->get_file();
        x = x1;
        y = y1;
        width = width1;
        height = height1;
        box = Box(x, x + width1, y, y + height1);
        screenWidth = scrW;
        screenHeight = scrH;
        name = "The Man";
        v = Vector(0, 0);
        sound = s;
        animations = sheet->parse_animations();
        animation = animations.at(2);
        type = spriteType;
        update_animation(1);
    }

    Sprite::Sprite(std::string arr[]) {
        name = arr[0];
        x = stof(arr[1]);
        y = stof(arr[2]);
        width = stof(arr[3]);
        height = stof(arr[4]);
        angle = stoi(arr[5]);
        istringstream(arr[6]) >> std::boolalpha >> is_spinning;
        screenWidth = stof(arr[7]);
        screenHeight = stof(arr[8]);
        if (strcmp("Player", arr[9].c_str()) == 0) {
            set_type(SpriteType::Player);
        }
        else if (strcmp("NPC", arr[9].c_str()) == 0) {
            set_type(SpriteType::NPC);
        }
        else if (strcmp("Nature", arr[9].c_str()) == 0) {
            set_type(SpriteType::Nature);
        }
        sto.width = width;
        sto.height = height;
        box = Box(x, x+width, y, y+height);
        v = Vector(0, 0);
    }

	Sprite::~Sprite() {
		destroy_texture(sti);
	}

    void Sprite::print() {
        cout << "\n\tName: " << name << " , x: " << x << ", y: " << y << ", width: " 
            << sto.width << ", height: " << sto.height << endl;
        cout << "\tBox MinX: " << box.getMinX() << ", MaxX: " << box.getMaxX() 
            << ", MinY: " << box.getMinY() << ", MaxY: " << box.getMaxY() << endl;
    }

	void Sprite::sleep(int milliseconds) {

		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	void Sprite::updateVector() {
		v = Vector();
		is_spinning = false;
		angle = 0;
		if (v.getX() < 0) {
			face_backwards = true;
		}
		else {
			face_backwards = false;
		}
	}

	void Sprite::passVector(Vector v1) {
		v = v1;
		is_spinning = false;
		if (v.getX() < 0) {
			face_backwards = true;
		}
		else {
			face_backwards = false;
		}
	}

    Box* Sprite::getOutline() {
        return &box;
    }

    void Sprite::reverseDirection(Vector::Direction d, float position) {
        if (type == NPC)
            v.reverseDirection(d);
        switch (d) {
        case Vector::LEFT_DIR:
        case Vector::RIGHT_DIR:
            set_x_pos(position);
            break;
        case Vector::TOP_DIR:
        case Vector::BOTTOM_DIR:
            set_y_pos(position);
            break;
        default:
            break;
        }
    }

    void Sprite::detectCollision(Sprite* s) {
        //Check if sprite is overlapping in x direction & reverse direction
        if (strcmp(s->get_nature_type().c_str(), "CaptureZone") != 0) {
            // Right Hand Check
            if (box.getMaxX() >= s->box.getMinX() && box.getMaxX() < s->box.getMaxX() && box.getMaxY() > s->box.getMinY() && box.getMinY() < s->box.getMaxY()) {
                cout << "Left Hand" << endl;
                reverseDirection(Vector::LEFT_DIR, box.getPrevMaxX() - 10);
                sound->getHit(0);
            }

            // Left Hand Check
            else if (box.getMinX() <= s->box.getMaxX() && box.getMinX() > s->box.getMinX() &&
                s->box.getMinY() < box.getMaxY() && s->box.getMaxY() > box.getMinY()) {
                cout << "Right Hand" << endl;
                reverseDirection(Vector::RIGHT_DIR, box.getPrevMinX() + box.getWidth() + 10);
                sound->getHit(0);
            }

            // Bottom Check
            else if (box.getMaxY() >= s->box.getMinY() && box.getMaxY() < s->box.getMaxY() &&
                s->box.getMaxX() > box.getMinX() && s->box.getMinX() < box.getMaxX()) {
                cout << "Top Check" << endl;
                reverseDirection(Vector::BOTTOM_DIR, box.getPrevMaxY() - 10);
                sound->getHit(0);
            }

            // Top Check
            else if (box.getMinY() <= s->box.getMaxY() && box.getMinY() > s->box.getMinY() &&
                s->box.getMinX() < box.getMaxX() && s->box.getMaxX() > box.getMinX()) {
                cout << "Bottom Check" << endl;
                reverseDirection(Vector::TOP_DIR, box.getPrevMinY() + box.getHeight() + 10);
                sound->getHit(0);
            }
        }
    }

    void Sprite::capture_zone(Sprite* s) {
        cout << s->get_nature_type() << " ";
        if (((box.getMaxX() >= s->box.getMinX() && box.getMaxX() <= s->box.getMaxX()) ||
            (box.getMinX() >= s->box.getMinX() && box.getMinX() <= s->box.getMaxX())) &&
            ((box.getMaxY() >= s->box.getMinY() && box.getMaxY() <= s->box.getMaxY()) ||
            (box.getMinY() <= s->box.getMaxY() && box.getMinY() >= s->box.getMaxY()))) {
            s->update_status(STATUS::CAPTURED);
        }
    }

    void Sprite::update_status(STATUS s) {

    }

    Sprite::STATUS Sprite::get_status() {
        return status;
    }

	void Sprite::update_sprite() {
		x = x + v.getX();
		y = y + v.getY();
        
        box.updateValues(v.getX(), v.getY());

        if (box.getMaxX() >= screenWidth) {
            reverseDirection(Vector::LEFT_DIR, screenWidth);
            sound->getHit(1);
        }
        else if (box.getMinX() <= 0) {
            reverseDirection(Vector::RIGHT_DIR, box.getWidth());
            sound->getHit(1);
        }
        else if (box.getMaxY() >= screenHeight) {
            reverseDirection(Vector::TOP_DIR, screenHeight);
            sound->getHit(1);
        }
        else if (box.getMinY() <= 0) {
            reverseDirection(Vector::BOTTOM_DIR, box.getHeight());
            sound->getHit(1);
        }

		if (is_spinning) {
			angle = angle + 10;
		}
        
	}

	void Sprite::draw_sprite(SDL_Rect cameraRect) {
        sti.m_dst.x = x - cameraRect.x;
        sti.m_dst.y = y - cameraRect.y;
        sti.m_dst.w = sto.width;
        sti.m_dst.h = sto.height;
        
		if (false) {
			render_texture(si, sti, x, y, angle, SDL_FLIP_HORIZONTAL, sto);
		}
		else {
			render_texture(si, sti, x, y, angle, SDL_FLIP_NONE, sto);
		}
	}

    void Sprite::set_animation(DIRECTION_FACING d) {
        int i = int(d);
        Animation *a = animations.at(i);
        set_CurrentAnimation(a);
    }

    int Sprite::update_animation(int frame) {
        int maxFrames = 0;
        if (curr_action == cge::ACTIVITY::IDLE) {
            maxFrames = 1;
        }
        else {
            maxFrames = animation->maxFrames;
        }
        
        sti.m_src.x = animation->x + animation->w * frame;
        sti.m_src.y = animation->y;
        sti.m_src.w = animation->w;
        sti.m_src.h = animation->h;
        
        frame++;
        if (frame >= maxFrames) {
            return 0;
        } else {
            return frame;
        }
    }

    string Sprite::convert_type() {
        int t = int(get_type());
        string MyStr(convert_type_enum[t]);
        return MyStr;
    }

    string Sprite::convert_status() {
        int r = int(get_status());
        string s(convert_status_enum[r]);
        return s;
    }

    SDLInfo Sprite::get_sdl_info() {
        return si;
    }

    SDLTextureOptions Sprite::get_sto() {
        return sto;
    }

    SDLTextureInfo Sprite::get_sti() {
        return sti;
    }

    std::string Sprite::get_name() {
        return name;
    }

    float Sprite::get_x_pos() {
        return x;
    }

    void Sprite::set_x_pos(float pos) {
        cout << x << " , " << pos << endl;
        x = box.moveXPos(pos);
        cout << x << endl;
    }

    float Sprite::get_center_x() {
        return x + float(sto.width / 2);
    }

    float Sprite::get_y_pos() {
        return y;
    }

    void Sprite::set_y_pos(float pos) {
        cout << y << " , " << pos << endl;
        y = box.moveYPos(pos);
        cout << y << endl;
    }

    float Sprite::get_center_y() {
        return y + float(sto.height / 2);
    }

    float Sprite::get_width() {
        return width;
    }

    float Sprite::get_height() {
        return height;
    }

    int Sprite::get_angle() {
        return angle;
    }

    bool Sprite::get_spinning() {
        return is_spinning;
    }

    float Sprite::get_screenwidth() {
        return screenWidth;
    }

    float Sprite::get_screenheight() {
        return screenHeight;
    }

    Sprite::SpriteType Sprite::get_type() {
        return type;
    }

    string Sprite::get_nature_type() {
        return natureType;
    }

    void Sprite::set_Name(string s) {
        name = s;
    }

    void Sprite::set_SDLInfo(SDLInfo si1) {
        si = si1;
    }

    void Sprite::set_Texture(cge::Texture t) {
        texture = t;
        sti = create_texture(si, t.get_motion(1));
    }

    void Sprite::set_SpriteSheet(SpriteSheet* s) {
        sheet = s;
        sti = create_texture(si, s->get_file());
        animations = sheet->parse_animations();
        animation = animations.at(2);
        update_animation(1);
    }

    void Sprite::set_screenWidth(float screenW) {
        screenWidth = screenW;
    }

    void Sprite::set_screenHeight(float screenH) {
        screenHeight = screenH;
    }

    void Sprite::set_Sound(Sound *s) {
        sound = s;
    }

    void Sprite::set_CurrentAnimation(Animation *a) {
        animation = a;
    }

    void Sprite::set_CurrentAction(ACTIVITY a) {
        curr_action = a;
    }

    void Sprite::set_type(Sprite::SpriteType t) {
        type = t;
    }

    void Sprite::set_nature_type(string type) {
        natureType = type;
    }

    void Sprite::set_status(STATUS s) {
        update_status(s);
    }
}
