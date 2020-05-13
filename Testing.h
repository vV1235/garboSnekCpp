#pragma once
class Testing {
private:
	static Testing* instance;
	Testing() {}
public:
	inline static Testing* getInstance() {
		if(!instance)
			instance = new Testing;
		return instance;
	}

	class Tetromino {
	public:
		Tetromino(std::string shape_) :
			shape{ shape_ } {
		};
		inline void displayShape() {
			std::cout << shape;
		}
		virtual inline void rotate() = 0;
	protected:
		std::string shape;
	};

	//tetris.fandom.com/wiki/Tetromino implement the rest of needed shapes...
	/*set shape of L to:
		#
		#   or ####
		#
		#
	*/
	class I : public Tetromino {
	public:
		I() :
			Tetromino("I") {
		};
		void rotate() {
			/*perform 90deg rotation on shape, side note: 
			check if you can rotate counterclockwise aswell as clockwise
			*/
		};
	};

	class L : public Tetromino {
	public:
		L() :
			Tetromino("L") {};
		void rotate() {
			//perform 90deg rotation on shape, side note:
		};
	};

	//---------------------------------------------------
	//Matrix for the 3D engine
	//template <typename T, int W, int H> ensure that T is a number with c++20s concepts
	class Mat4 {
	public:
		int i;
		int arr[2][5] = { 
			{1,2,3,4,5},
			{6,7,8,9,10}
		};
		Mat4 operator+(const Mat4& b) {
			Mat4 tmp;
			tmp.i = this->i + b.i;
			return tmp;
		};
		Mat4 operator-(const Mat4& b) {
			Mat4 tmp;
			tmp.i = this->i - b.i;
			return tmp;
		};
		//etc... for multiplication and division
		//create functions for getting the det(matrix), transposition, inverse and whatever else there is
		friend std::ostream& operator<<(std::ostream& output, const Mat4& mat) {
			//extend functionality as the matrix complexity grows
			output << mat.i;
			return output;
		}
		friend std::istream& operator>>(std::istream& input, Mat4& mat) {
			//extend functionality as the matrix complexity grows
			input >> mat.i;
			return input;
		}
		int operator() (unsigned r, unsigned c) {
			//Access matrix indices later on
			return arr[r][c];
		};
	};
};

Testing* Testing::instance = 0;

