#pragma once

const int ScreenWidth = 1000;
const int ScreenHeight = 800;

const float Friction = .02f;

const float PlayerHeight = 35.f;
const float PlayerWidth = 35.f;
const float PlayerMaxSpeed = 400.f;

const float VampireHeight = 32.0f;
const float VampireWidth = 32.0f;
const float VampireSpeed = 65.0f;

const float LanceWidth = 100.f;
const float LanceHeight = 15.f;

const float BulletRadius = 6.f;
const float BulletWidth = 4.f;
const float BulletHeight = 4.f;

const int GridSize = 16;

const float TileSizeX = ScreenWidth / (float)GridSize;
const float TileSizeY = ScreenHeight / (float)GridSize;