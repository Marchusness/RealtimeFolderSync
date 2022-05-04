#include "thing.h"
#include "engine.h"

Thing::Thing(b2World* world)
{
    sprite;
    sprite.setTexture(*Engine::getTexture("block1x1"));
    sprite.setOrigin(128, 128);

	float SCALE = 30;
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(10 / SCALE, 10 / SCALE);
	BodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);
}

Thing::~Thing()
{
}

void Thing::update()
{
}

void Thing::draw()
{
    //just quick test stuff
    sprite.setColor(sf::Color(0, 255, 0));
	sprite.setPosition(30 * body->GetPosition().x, 30 * body->GetPosition().y);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
    Engine::getWindow()->draw(sprite);

}