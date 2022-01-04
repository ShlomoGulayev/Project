#include "Board.h"

using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;

//---------------------------------------------------
Board::Board()
	:m_rows(0), m_cols(0), m_characters(nullptr)
{}
//---------------------------------------------------
void Board::setBoard(sf::Texture textures[], vector< unique_ptr <MovingObject > >& characters)
{
	ifstream in;
	in.open("Board.txt");	//open the file
	if (!in.is_open())
	{
		cerr << "could not open the file -" << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	int i = 0;
	
	while (getline(in, line))
	{
		m_board.push_back(line);
		m_cols = (int)line.size();
		i++;
	}
	m_rows = i;
	in.close();
	
	m_characters = &characters;
	createObject(textures);
}

//---------------------------------------------------
void Board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_characters[0].size(); i++)
		m_characters[0][i]->draw(window);
	for (int i = 0; i < m_static_objects.size(); i++)
		m_static_objects[i]->draw(window);
}

//---------------------------------------------------
static std::unique_ptr<MovingObject> createMovableObject(const char c,
													     sf::Vector2f& loc,
														 sf::Texture textures[])
{
	switch (c)
	{
	case 'K': return std::make_unique<King>(loc, textures[KING]);
	case 'M': return std::make_unique<Mage>(loc, textures[MAGE]);
	case 'W': return std::make_unique<Warrior>(loc, textures[WARRIOR]);
	case 'T': return std::make_unique<Thief>(loc, textures[THIEF]);
	case '^': return std::make_unique<Gnome>(loc, textures[GNOME]);
	}
	return nullptr;
}
//---------------------------------------------------
static std::unique_ptr<StaticObject> createStaticObject(const char c,
												        sf::Vector2f& loc,
													    sf::Texture textures[])
{
	switch (c)
	{
	case '*': return std::make_unique<Fire>(loc, textures[FIRE]);
	case 'F': return std::make_unique<Key>(loc, textures[KEY]);
	case '=': return std::make_unique<Wall>(loc, textures[WALL]);
	case '#': return std::make_unique<Gate>(loc, textures[GATE]);
	case '!': return std::make_unique<Ogre>(loc, textures[ORGE]);
	case '@': return std::make_unique<Throne>(loc, textures[THRONE]);
	case 'X': return std::make_unique<Teleport>(loc, textures[PORTAL]);
	}
	return nullptr;
}
//---------------------------------------------------
void Board::createObject(sf::Texture textures[])
{
	int width_space = BOARD_WIDTH / m_cols;
	int height_space = BOARD_HEIGHT / m_rows;
	std::unique_ptr<MovingObject> gnome = nullptr;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			sf::Vector2f loc((col * width_space), WINDOW_HEIGHT - BOARD_HEIGHT + (row * height_space));
			char c = m_board[row][col];
			if (c == 'K' || c == 'M' || c == 'W' || c == 'T')
			{
				std::unique_ptr<MovingObject> movable = createMovableObject(c, loc, textures);
				m_characters->push_back(std::move(movable));
			}
			else if (c == '^')
			{
				gnome = createMovableObject(c, loc, textures);
			}
			else if (c != ' ')
			{
				std::unique_ptr<StaticObject> unmovable = createStaticObject(c, loc, textures);
				m_static_objects.push_back(std::move(unmovable));
			}
		}
	}
	if (gnome != nullptr)
	{
		m_characters->push_back(std::move(gnome));
	}
}