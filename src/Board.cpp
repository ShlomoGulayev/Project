#include "Board.h"

//-------------------------------------------------------------------------
Board::Board()
	:m_rows(0), m_cols(0), m_characters(nullptr), m_static_objects(nullptr)
{
	setLine();
}
//-------------------------------------------------------------------------
void Board::setBoard(std::vector< std::unique_ptr <MovingObject > > &characters, 
					 std::vector< std::unique_ptr <StaticObject > > &static_objects)
{
	std::ifstream in;
	in.open("Board.txt");
	if (!in.is_open())
	{
		std::cerr << "could not open the file -" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string line;
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
	m_static_objects = &static_objects;
	
	createObject();
	resizeObjects();
}
//-------------------------------------------------------------------------
void Board::setLine()
{
	m_line.setSize(sf::Vector2f(WINDOW_WIDTH, 2));
	m_line.setFillColor(sf::Color::Black);
	m_line.setPosition(sf::Vector2f(0, BOARD_HEIGHT));
}
//-------------------------------------------------------------------------
void Board::draw(sf::RenderWindow& window) const
{
	for (auto& static_object : *m_static_objects)
		static_object->draw(window);
	for (auto& moving_object : *m_characters)
		moving_object->draw(window);
	window.draw(m_line);
}
//-------------------------------------------------------------------------
static std::unique_ptr<MovingObject> createMovingObject(const char c,
													     sf::Vector2f& loc)
{
	switch (c)
	{
	case 'K': return std::make_unique<King>(loc, Singleton::instance().getObjectTexture(KING));
	case 'M': return std::make_unique<Mage>(loc, Singleton::instance().getObjectTexture(MAGE));
	case 'W': return std::make_unique<Warrior>(loc, Singleton::instance().getObjectTexture(WARRIOR));
	case 'T': return std::make_unique<Thief>(loc, Singleton::instance().getObjectTexture(THIEF));
	case '^': return std::make_unique<Gnome>(loc, Singleton::instance().getObjectTexture(GNOME));
	}
	return nullptr;
}
//-------------------------------------------------------------------------
static std::unique_ptr<StaticObject> createStaticObject(const char c,
												        sf::Vector2f& loc)
{
	switch (c)
	{
	case '*': return std::make_unique<Fire>(loc, Singleton::instance().getObjectTexture(FIRE));
	case 'F': return std::make_unique<Key>(loc, Singleton::instance().getObjectTexture(KEY));
	case '=': return std::make_unique<Wall>(loc, Singleton::instance().getObjectTexture(WALL));
	case '#': return std::make_unique<Gate>(loc, Singleton::instance().getObjectTexture(GATE));
	case '!': return std::make_unique<Ogre>(loc, Singleton::instance().getObjectTexture(OGRE));
	case '@': return std::make_unique<Throne>(loc, Singleton::instance().getObjectTexture(THRONE));
	case 'X': return std::make_unique<Teleport>(loc, Singleton::instance().getObjectTexture(TELEPORT));
	case '$': 
	{
		int type = rand() % 3 + 1;
		switch (type)
		{
		case 1: return std::make_unique<Gift1>(loc, Singleton::instance().getObjectTexture(GIFT));
		case 2: return std::make_unique<Gift2>(loc, Singleton::instance().getObjectTexture(GIFT));
		case 3: return std::make_unique<Gift3>(loc, Singleton::instance().getObjectTexture(GIFT));
		}
	}
	}
	return nullptr;
}
//-------------------------------------------------------------------------
void Board::createObject()
{
	float width_object_scale =  (float)BOARD_WIDTH / (float)m_cols;
	float height_object_scale = (float)BOARD_HEIGHT / (float)m_rows;
	int index_movable = 0;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			sf::Vector2f loc((col * width_object_scale) + width_object_scale*0.5, 
							 (row * height_object_scale) + height_object_scale*0.5);
			char c = m_board[row][col];
			
			if (c == 'K' || c == 'M' || c == 'W' || c == 'T' || c == '^')
			{
				std::unique_ptr<MovingObject> moving_object = createMovingObject(c, loc);
				m_characters->push_back(std::move(moving_object));
				index_movable++;
			}
			else if (c != ' ')
			{
				std::unique_ptr<StaticObject> static_object = createStaticObject(c, loc);
				m_static_objects->push_back(std::move(static_object));
			}
			if (c == 'X')
				m_teleports.push_back(std::make_unique<sf::Vector2f>(loc));
			if (c == '^')
				m_index_gnomes.push_back(index_movable-1);
		}
	}
}
//-------------------------------------------------------------------------
void Board::resizeObjects()
{
	float width_object_scale = (float)BOARD_WIDTH / (float)m_cols;
	float height_object_scale = (float)BOARD_HEIGHT / (float)m_rows;

	for (auto& moving_object : *m_characters)
		moving_object->setSpriteScale(width_object_scale / (float)(OBJECT_SIZE_PIXEL + 20),
									  height_object_scale / (float)(OBJECT_SIZE_PIXEL + 20));

	for (auto& static_object : *m_static_objects)
		static_object->setSpriteScale(width_object_scale / (float)(OBJECT_SIZE_PIXEL + 5),
								      height_object_scale / (float)(OBJECT_SIZE_PIXEL + 5));
}
//-------------------------------------------------------------------------
const sf::Vector2f& Board::findNextLocationTeleport(const sf::Vector2f& loc)
{
	for (int i = 0; i < m_teleports.size(); i++)
	{
		if (*(m_teleports[i]) == loc)
		{
			if (i % 2 == 0)
				return *(m_teleports[i + 1]);
			else
				return *(m_teleports[i - 1]);
		}
	}
	return sf::Vector2f();
}
//-------------------------------------------------------------------------
int Board::getGnomeSize() const
{
	return m_index_gnomes.size();
}
//-------------------------------------------------------------------------
int Board::getGnome(const int index) const
{
	return m_index_gnomes[index];
}
//-------------------------------------------------------------------------
void Board::eraseGnomes()
{
	m_index_gnomes.clear();
}