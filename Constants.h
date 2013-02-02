#ifndef CONSTANTS_H
#define CONSTANTS_H

// MOTORS

static const int LEFT_DRIVE_PWM = 1;
static const int RIGHT_DRIVE_PWM = 2;

// CONTROLS

static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;

// SENSORS

static const int LEFT_ENCODER_A = 11;
static const int LEFT_ENCODER_B = 12;
static const int RIGHT_ENCODER_A = 13;
static const int RIGHT_ENCODER_B = 14;

static const int GYRO_CHANNEL = 2;
static const float GYRO_SENSITIVITY = 0.007; // 7 mV/deg/sec

// ENCODER PID
static const float ENCODER_P = 0.019;
static const float ENCODER_I = 0.0;
static const float ENCODER_D = 0.016;

// GYRO PID
static const float GYRO_P = -0.03;
static const float GYRO_I = -0.003;
static const float GYRO_D = -0.05;

// DRIVE STRAIGHT
static const float DRIVE_STRAIGHT_P = 0.002;

// Encoders are geared at a 1:1 ratio.
// TODO: Configuration for left and right sides of drivetrain.
static const double TIRE_CIRCUMFERENCE = 27.75; 	// in inches
static const double COUNTS_PER_REVOLUTION = 128.0;
static const double INCHES_PER_COUNT = TIRE_CIRCUMFERENCE / COUNTS_PER_REVOLUTION;

#endif
