#include "Board.h"

//-------------------------------------------------------------------------
Board::Board()
	:m_rows(0), m_cols(0), m_height_object_scale(0), m_width_object_scale(0),
	 m_characters(nullptr), m_static_objects(nullptr)
{}
//-------------------------------------------------------------------------
void Board::setBoard(sf::Texture textures[], 
					 std::vector< std::unique_ptr <MovingObject > > &characters, 
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
	
	createObject(textures);
	resizeObjects();
}
//-------------------------------------------------------------------------
void Board::draw(sf::RenderWindow& window) const
{
	for (auto& static_object : *m_static_objects)
		static_object->draw(window);
	for (auto& moving_object : *m_characters)
		moving_object->draw(window);
}
//-------------------------------------------------------------------------
static std::unique_ptr<MovingObject> createMovingObject(const char c,
													     sf::Vector2f& loc,
														 sf::Texture textures[])
{
	switch (c)
	{
	case 'K': return std::make_unique<King>(loc, textures[KING]);
	case 'M': return std::make_unique<Mage>(loc, textures[MAGE]);
	case 'W': return std::make_unique<Warrior>(loc, textures[WARRIOR]);
	case 'T': return std::make_unique<Thief>(loc, textures[THIEF]);
	}
	return nullptr;
}
//-------------------------------------------------------------------------
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
	case '!': return std::make_unique<Ogre>(loc, textures[OGRE]);
	case '@': return std::make_unique<Throne>(loc, textures[THRONE]);
	case 'X': return std::make_unique<Teleport>(loc, textures[TELEPORT]);
	}
	return nullptr;
}
//-------------------------------------------------------------------------
void Board::createObject(sf::Texture textures[])
{
	m_width_object_scale =  (float)BOARD_WIDTH / (float)m_cols;
	m_height_object_scale = (float)BOARD_HEIGHT / (float)m_rows;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			sf::Vector2f loc((col * m_width_object_scale) + m_width_object_scale*0.5, 
							 (row * m_height_object_scale) + m_height_object_scale*0.5);
			char c = m_board[row][col];
			if (c == 'K' || c == 'M' || c == 'W' || c == 'T')
			{
				std::unique_ptr<MovingObject> moving_object = createMovingObject(c, loc, textures);
				m_characters->push_back(std::move(moving_object));
			}
			else if (c != ' ')
			{
				std::unique_ptr<StaticObject> static_object = createStaticObject(c, loc, textures);
				m_static_objects->push_back(std::move(static_object));
			}
			if (c == 'X')
				m_teleports.push_back(std::make_unique<sf::Vector2f>(loc));
		}
	}
}
//-------------------------------------------------------------------------
void Board::resizeObjects()
{
	for (auto& moving_object : *m_characters)
		moving_object->setSpriteScale(m_width_object_scale / (float)(OBJECT_SIZE_PIXEL + 10),
									  m_height_object_scale / (float)(OBJECT_SIZE_PIXEL + 10));

	for (auto& static_object : *m_static_objects)
		static_object->setSpriteScale(m_width_object_scale / (float)(OBJECT_SIZE_PIXEL + 5),
								      m_height_object_scale / (float)(OBJECT_SIZE_PIXEL + 5));
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
}
//-------------------------------------------------------------------------
float Board::getWidthObject() const
{
	return m_width_object_scale;
}
//-------------------------------------------------------------------------
float Board::getHeightObject() const
{
	return m_height_object_scale;
}