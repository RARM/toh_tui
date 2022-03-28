#ifndef _TOH_Engine_H_
#define _TOH_Engine_H_

#include <vector>

// Creating a simple structure to represent a disk.
struct Disk
{
	unsigned id = 0;
	struct Disk* next = nullptr;
};

// The STL stack doesn't work for this project because I need a function to read all the elements in the stack without modifing them.
// Therefore, I am creating my own stack structure for this specific project.
class Rod_Stack
{
public:
	Rod_Stack();

	// Rule of three.
	
	~Rod_Stack();									// I. Destructor.
	Rod_Stack(const Rod_Stack& other);				// II. Copy Constructor.
	Rod_Stack& operator=(const Rod_Stack& other);	// III. Copy Assignment.

	// Return the size of the stack.
	size_t size();

	// Get the value of the top disk.
	unsigned peek() { return (this->top == nullptr) ? 0 : this->top->id; }

	// Push a disk to the top of the stack.
	void push(unsigned disk);

	// Removes the top disk.
	void pop();

	// Clears the current stack.
	void clear();

	// Get state of the current Rod as a vector.
	std::vector<unsigned> get_state();

private:
	struct Disk* top;

	// Helper functions.

	// Deallocates all the disks in the current memory. The top pointer is not set to nullptr.
	void del();
};

// Structure representing the state of the game.
typedef struct Game_State_Structure
{
	std::vector<int> A, B, C;
} Rods;

// Game Engine.
// Manages game by setting or getting the current state.
class ToH_Game
{
public:
	// Creates a game with three disks by default.
	ToH_Game(size_t disks_amount = 3);
	
	// Rule of three. Is it neccessary in this case?

	// ~ToH_Game();
	// ToH_Game(const ToH_Game& other);
	// ToH_Game& operator=(const ToH_Game& other);

	// Make a move. Return true if move was successful/legal; false otherwise (no move was made).
	bool move(size_t source_rod, size_t dest_rod);

	// Returns an object representing the current state of the game.
	Rods get_state();

	// Check if win (when the disks are all in rod C).
	bool is_solved();

	// Constants representing each rod.
	
	static constexpr int rod_A{ 0 };
	static constexpr int rod_B{ 1 };
	static constexpr int rod_C{ 2 };

private:
	Rod_Stack rods[3];
	const size_t disks_amount;
};

#endif