/******************* IR CODES ************/

int irQuit[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 50,
	58, 52,
	58, 52,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	58, 52,
	58, 162,
	58, 52,
	58, 52,
	58, 52,
	58, 162,
	56, 54,
	56, 52,
	58, 162,
	58, 52,
	58, 162,
	56, 164,
	56, 164,
	58, 50,
	58, 162,
	58, 3934,
	892, 216,
	58, 2874,
	892, 218,
	60, 0};

int irMode[] = {
// ON, OFF (in 10's of microseconds)
	892, 438,
	56, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	56, 54,
	56, 54,
	58, 160,
	58, 162,
	58, 162,
	60, 160,
	56, 162,
	58, 162,
	58, 162,
	58, 162,
	56, 54,
	56, 162,
	58, 162,
	58, 52,
	58, 52,
	56, 54,
	56, 164,
	56, 52,
	58, 162,
	58, 52,
	56, 54,
	56, 164,
	56, 162,
	58, 162,
	58, 52,
	58, 162,
	56, 3934,
	892, 218,
	56, 0};

int irMute[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 52,
	60, 50,
	60, 48,
	60, 50,
	58, 52,
	60, 50,
	60, 50,
	60, 50,
	60, 158,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 50,
	60, 50,
	58, 52,
	58, 162,
	58, 52,
	58, 50,
	62, 48,
	62, 48,
	58, 162,
	58, 162,
	58, 160,
	62, 48,
	60, 160,
	62, 3930,
	896, 212,
	58, 2874,
	894, 216,
	58, 2874,
	894, 214,
	58, 0};

int irPrev[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 52,
	58, 52,
	58, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	56, 164,
	56, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	56, 162,
	58, 52,
	58, 52,
	58, 162,
	56, 54,
	56, 54,
	56, 52,
	58, 162,
	58, 52,
	58, 162,
	58, 162,
	58, 52,
	56, 162,
	58, 162,
	58, 162,
	54, 56,
	56, 164,
	56, 3934,
	894, 216,
	58, 0};

int irNext[] = {
// ON, OFF (in 10's of microseconds)
	894, 434,
	58, 52,
	60, 50,
	60, 50,
	58, 52,
	58, 52,
	56, 54,
	56, 52,
	58, 52,
	58, 162,
	58, 162,
	56, 162,
	58, 162,
	58, 162,
	58, 162,
	60, 160,
	58, 160,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 50,
	58, 162,
	58, 52,
	58, 162,
	58, 162,
	58, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 52,
	58, 162,
	58, 3932,
	892, 216,
	58, 0};

int irPlayPause[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 52,
	58, 50,
	62, 48,
	60, 50,
	58, 52,
	58, 52,
	58, 50,
	62, 48,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	60, 160,
	62, 158,
	58, 160,
	60, 160,
	60, 160,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	56, 162,
	58, 52,
	58, 52,
	60, 50,
	58, 162,
	58, 160,
	58, 162,
	58, 162,
	58, 52,
	58, 162,
	56, 3934,
	894, 214,
	58, 2874,
	894, 216,
	56, 0};

int irVolDecrease[] = {
// ON, OFF (in 10's of microseconds)
	896, 434,
	58, 52,
	60, 50,
	60, 50,
	58, 50,
	58, 52,
	58, 52,
	60, 50,
	60, 50,
	58, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	56, 54,
	56, 52,
	58, 162,
	58, 162,
	58, 162,
	56, 164,
	56, 162,
	58, 3934,
	892, 216,
	60, 0};

int irVolIncrease[] = {
// ON, OFF (in 10's of microseconds)
	894, 434,
	60, 50,
	58, 52,
	60, 50,
	60, 50,
	58, 52,
	58, 50,
	58, 52,
	62, 48,
	58, 162,
	60, 160,
	56, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	56, 162,
	58, 162,
	58, 52,
	58, 162,
	58, 52,
	58, 160,
	58, 52,
	58, 52,
	58, 52,
	60, 50,
	58, 160,
	62, 48,
	58, 162,
	58, 52,
	58, 162,
	58, 162,
	56, 162,
	58, 3934,
	890, 218,
	56, 0};

int irZero[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	58, 52,
	58, 52,
	58, 52,
	60, 48,
	60, 50,
	58, 52,
	60, 50,
	58, 52,
	60, 160,
	58, 162,
	58, 160,
	62, 158,
	58, 162,
	58, 162,
	60, 158,
	58, 162,
	58, 52,
	58, 162,
	58, 162,
	56, 54,
	56, 162,
	58, 52,
	58, 52,
	60, 50,
	58, 160,
	60, 50,
	58, 52,
	60, 160,
	58, 52,
	58, 162,
	58, 160,
	58, 162,
	58, 3932,
	894, 216,
	58, 0};

int irHundredPlus[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	56, 52,
	60, 50,
	60, 50,
	62, 48,
	60, 160,
	58, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	58, 162,
	58, 52,
	60, 50,
	58, 160,
	62, 158,
	58, 52,
	58, 52,
	58, 52,
	60, 50,
	58, 162,
	56, 162,
	58, 52,
	58, 52,
	58, 162,
	58, 162,
	56, 162,
	58, 3934,
	892, 216,
	58, 0};

int irBack[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	58, 52,
	58, 52,
	58, 52,
	58, 50,
	58, 52,
	58, 52,
	60, 50,
	58, 52,
	58, 162,
	58, 162,
	56, 162,
	60, 160,
	62, 158,
	58, 162,
	58, 162,
	60, 158,
	58, 162,
	58, 52,
	58, 162,
	58, 162,
	56, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 160,
	60, 50,
	58, 52,
	58, 162,
	58, 162,
	58, 160,
	62, 158,
	58, 3934,
	894, 214,
	58, 0};

int irOne[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	58, 52,
	62, 48,
	58, 52,
	58, 50,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 162,
	60, 158,
	60, 160,
	60, 160,
	58, 162,
	60, 160,
	58, 160,
	58, 162,
	58, 52,
	62, 48,
	60, 160,
	58, 160,
	58, 52,
	60, 50,
	58, 52,
	58, 52,
	58, 162,
	58, 160,
	58, 52,
	58, 52,
	58, 162,
	58, 162,
	58, 160,
	58, 162,
	58, 3934,
	892, 216,
	58, 0};

int irTwo[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	56, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	56, 52,
	58, 52,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 162,
	58, 50,
	58, 52,
	58, 52,
	58, 162,
	58, 162,
	58, 52,
	56, 52,
	58, 52,
	58, 162,
	58, 162,
	58, 162,
	58, 52,
	56, 54,
	56, 162,
	58, 162,
	58, 162,
	58, 3932,
	894, 216,
	58, 0};

int irThree[] = {
// ON, OFF (in 10's of microseconds)
	892, 436,
	58, 52,
	58, 52,
	58, 50,
	60, 50,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 160,
	60, 160,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	60, 50,
	58, 162,
	60, 160,
	58, 160,
	60, 160,
	60, 50,
	60, 160,
	58, 52,
	58, 162,
	58, 52,
	58, 50,
	60, 50,
	58, 52,
	58, 162,
	58, 52,
	58, 160,
	60, 3932,
	892, 216,
	60, 0};

int irFour[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 50,
	60, 50,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 52,
	58, 50,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	60, 160,
	58, 162,
	58, 52,
	58, 52,
	58, 52,
	58, 160,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 160,
	60, 160,
	60, 160,
	58, 52,
	58, 162,
	58, 160,
	60, 160,
	60, 160,
	58, 3932,
	894, 216,
	58, 0};

int irFive[] = {
// ON, OFF (in 10's of microseconds)
	896, 434,
	58, 52,
	58, 50,
	60, 50,
	60, 50,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	58, 160,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	60, 160,
	60, 50,
	58, 52,
	58, 162,
	58, 162,
	58, 160,
	60, 50,
	60, 50,
	60, 50,
	58, 162,
	60, 160,
	58, 52,
	58, 50,
	60, 50,
	62, 158,
	60, 160,
	58, 162,
	58, 3932,
	894, 216,
	60, 2874,
	892, 216,
	62, 0};

int irSix[] = {
// ON, OFF (in 10's of microseconds)
	896, 434,
	60, 50,
	58, 52,
	58, 52,
	58, 50,
	60, 50,
	60, 50,
	58, 52,
	58, 52,
	58, 160,
	60, 160,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	62, 158,
	60, 50,
	58, 162,
	60, 50,
	58, 160,
	60, 160,
	60, 50,
	58, 162,
	58, 52,
	58, 160,
	60, 50,
	60, 160,
	60, 50,
	58, 52,
	58, 162,
	58, 50,
	60, 160,
	62, 3930,
	894, 214,
	62, 0};

int irSeven[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 52,
	58, 50,
	58, 52,
	58, 52,
	60, 50,
	58, 52,
	58, 52,
	58, 50,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 160,
	60, 160,
	58, 162,
	60, 160,
	58, 52,
	58, 162,
	58, 50,
	60, 50,
	60, 50,
	60, 50,
	58, 162,
	58, 52,
	58, 162,
	58, 50,
	60, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 52,
	58, 160,
	60, 0};

int irEight[] = {
// ON, OFF (in 10's of microseconds)
	894, 436,
	58, 52,
	58, 50,
	60, 50,
	58, 52,
	60, 50,
	58, 52,
	58, 52,
	58, 52,
	60, 158,
	60, 160,
	60, 160,
	58, 162,
	60, 160,
	58, 160,
	60, 160,
	58, 162,
	58, 52,
	58, 162,
	58, 52,
	58, 50,
	62, 158,
	58, 52,
	58, 162,
	58, 52,
	60, 158,
	58, 52,
	60, 160,
	58, 162,
	58, 52,
	60, 158,
	58, 52,
	60, 160,
	58, 3932,
	896, 214,
	58, 0};

int irNine[] = {
// ON, OFF (in 10's of microseconds)
	896, 434,
	58, 52,
	58, 52,
	60, 48,
	60, 50,
	58, 52,
	62, 48,
	58, 52,
	60, 50,
	58, 160,
	60, 160,
	58, 162,
	58, 162,
	58, 162,
	58, 160,
	58, 162,
	58, 162,
	58, 52,
	58, 162,
	58, 52,
	58, 160,
	58, 52,
	58, 52,
	58, 162,
	58, 52,
	58, 162,
	58, 50,
	60, 160,
	58, 52,
	58, 162,
	58, 162,
	58, 52,
	58, 160,
	58, 3934,
	894, 216,
	56, 0};