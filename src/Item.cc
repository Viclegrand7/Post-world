#ifndef RV_ZD_ITEM_H
#define RV_ZD_ITEM_H
#include "Item.hh"
#endif

Item :: Item(const Vector3f &rotation, const Vector3f &scale, const CollisionSphere &cs, int id, int texture)
	: att_rotation(rotation), att_scale(scale), att_collSphere(cs), att_id(id), att_texture(texture) {}



void Inventory :: add(const Vector3f &rotation, const Vector3f &scale, const CollisionSphere &cs, int id, int texture) {
	att_items.emplace_back(Item(rotation, scale, cs, id, texture));
}

void Inventory :: del(int id) {
	for (std :: vector <Item> :: iterator it = att_items.begin() ; it != att_items.end() ; ++it)
		if (it->att_id == id) {
			att_items.erase(it);
			break;
		}
}

int Inventory :: update(const CollisionSphere &playerPos) {
	for (std :: vector <Item> :: iterator it = att_items.begin() ; it != att_items.end() ; ++it) {
		it->att_rotation.att_y += 1;
		if (it->att_rotation.att_y >= 360)
			it->att_rotation.att_y -= 360;
		if (Collision :: sphereSphere(it->att_collSphere, playerPos)) {
			int tmp(it->att_id);
			att_items.erase(it);
			return tmp;
		}
	}
	return -1;
}

void Inventory :: display() {
	for (std :: vector <Item> :: iterator it = att_items.begin() ; it != att_items.end() ; ++it) {
		glPushMatrix(); //Saves prev Matrix

		glTranslatef(it->att_collSphere.att_center.att_x, it->att_collSphere.att_center.att_y, it->att_collSphere.att_center.att_z);
		glRotatef(it->att_rotation.att_x, 1, 0, 0);
		glRotatef(it->att_rotation.att_y, 0, 1, 0);
		glRotatef(it->att_rotation.att_z, 0, 0, 1);
		glScalef(it->att_scale.att_x, it->att_scale.att_y, it->att_scale.att_z);
		glCallList(it->att_texture);

		glPopMatrix(); //Gets back to prev Matrix
	}
}