#include <SPI.h>

/*
  Obstacle.ino - Make elegoo smart robot car v1.0 avoid obstacles
  Created by Pablo Gambetta December 2016
  Released into the public domain.
*/

// [esp] Incluir librerias necesarias para la conectividad y la conduccion del auto
// [eng] Include libraries necessary for the connectivity and driving of the car
#include <IRremote.h>
#include <Drivelib.h>
#include <Eyeslib.h>

// [esp] Incluir drivelib
// [eng] Include drivelib
Drivelib drivelib;
// [esp] Incluir eyeslib
// [eng] Include eyeslib
Eyeslib eyeslib;

int LEFTECHO = A0;
int LEFTTRIG = A1;
int RIGHTECHO = A4;
int RIGHTTRIG = A5;

int distance = 0;
int rightDistance = 0;
int leftDistance = 0;
int last_turn = 0;
int right = 1;
int left = 2;

int mindistance_fast = 100;
int mindistance_normal = 80;
int mindistance_slow = 60;
int mindistance_stop = 40;

bool collide()
{
	rightDistance = eyeslib.distance(eyeslib.right);
	if (rightDistance <= mindistance_stop)
	{
		//drivelib.stop();
		Serial.print("collide right distance => STOP");
		delay(500);
		return true;
	}
	leftDistance = eyeslib.distance(eyeslib.left);
	if (leftDistance <= mindistance_stop)
	{
		//drivelib.stop();
		Serial.print("collide left distance => STOP");
		delay(500);
		return true;
	}
	delay(100);
	return false;
}

void get_sides_distance()
{
	rightDistance = eyeslib.distance(eyeslib.right);
	leftDistance = eyeslib.distance(eyeslib.left);
	Serial.print("rightDistance=");
	Serial.println(rightDistance);
	Serial.println("; leftDistance=");
	Serial.println(leftDistance);
}

void choose_speed()
{
	if (distance >= mindistance_fast && rightDistance >= mindistance_fast && leftDistance >= mindistance_fast)
	{
		//drivelib.speed(255);
	}
	else if (distance >= mindistance_normal && rightDistance >= mindistance_normal && leftDistance >= mindistance_normal)
	{
		//drivelib.speed(127);
	}
	else if (distance >= mindistance_slow && rightDistance >= mindistance_slow && leftDistance >= mindistance_slow)
	{
		//drivelib.speed(63);
	}
}

/**
* [esp] Funcion que elige hacia a donde debe ir el auto
* [eng] Function that chooses to where the car should go
*/
void choose_direction()
{
	// [esp] Obtener la distancia de los costados
	// [eng] get sides distances
	get_sides_distance();
	if ((rightDistance <= mindistance_slow) && (leftDistance <= mindistance_slow))
	{
		// [esp] Si no hay lugar para girar, retroceder
		// [eng] If there is no place to rotate, go back
		//drivelib.backward();
		delay(200);
		//drivelib.breakcar();
		last_turn = 0;
	}
	else if (last_turn == right || (rightDistance > leftDistance) == left || rightDistance > leftDistance)
	{
		// [esp] Si hay mas distancia a la derecha, girar hacia la derecha
		// [eng] If there is more distance to the right, turn right
		//drivelib.right();
		delay(200);
		//drivelib.breakcar();
		last_turn = right;
	}
	else if (last_turn == left || rightDistance < leftDistance)
	{
		// [esp] Si hay mas distancia a la izquierda, girar hacia la izquierda
		// [eng] If there is more distance to the left, turn left
		//drivelib.left();
		delay(200);
		//drivelib.breakcar();
		last_turn = left;
	}
}

/**
* [esp] Funcion de configuracion. Corre unicamente una vez. 
* [eng] Setup function. Only run once.
*/
void setup()
{
	Serial.begin(9600);
	Serial.print("Setup");
	// [esp] Inicializar librerias
	// [eng] Initialize libraries
	drivelib.init();
	// [esp] Inicializar ojo izquierdo
	// [eng] Initialize left eye
	eyeslib.setEye(LEFTECHO, LEFTTRIG, eyeslib.left);
	// [esp] Inicializar ojo derecho
	// [eng] Initialize right eye
	eyeslib.setEye(RIGHTECHO, RIGHTTRIG, eyeslib.right);
}

/**
* [esp] Funcion principal. Corre indefinidamente.
* [eng] Main function. Runs repeatedly.
*/
void loop()
{
	// [esp] Analizar si colisiono
	// [eng] Analyze if it collided
	if (collide())
	{
		// [esp] Se detecto una colision, ver que direccion tomar
		// [eng] A collision is detected, see which direction to take
		choose_direction();
	}
	else
	{
		// [esp] Dependiendo de la distancia, acelerar o desacelerar
		// [eng] Depending on the distance, accelerate or decelerate
		choose_speed();
		// [esp] No hay moros en la costa, avanzar
		// [eng] You can go forward
		//drivelib.forward();
		Serial.print("foward");
		last_turn = 0;
	}
}
