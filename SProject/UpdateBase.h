#pragma once
class UpdateBase
{
private:
	bool m_Death;
	bool m_Update;

public:
	UpdateBase();
	virtual ~UpdateBase();

public:
	void On()
	{
		m_Update = true;
	}
	void Off()
	{
		m_Update = false;
	}
	void Die()
	{
		m_Death = true;
	}

public:
	virtual bool DeathCheck()
	{
		return true == m_Death;
	}
	virtual bool UpdateCheck()
	{
		return true == m_Update && false == m_Death;
	}
};

