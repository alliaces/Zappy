package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Eggs {
	
	int id;
	int x;
	int y;
	int mapx;
	int mapy;
	Sprite egg;
	boolean d3 = false;
	
	public void resize()
	{
		egg.setSize((Gdx.graphics.getWidth() / mapx) / 5, (Gdx.graphics.getHeight() / mapy) / 5);
	}
	
	public Eggs(Sprite egg,int id, int x, int y, int mapx, int mapy)
	{
		this.egg = egg;
		this.x = x;
		this.y = y;
		this.mapx = mapx;
		this.mapy = mapy;
		egg.setSize((Gdx.graphics.getWidth() / mapx) / 5, (Gdx.graphics.getHeight() / mapy) / 5);
	}

	public void draw(SpriteBatch batch)
	{
		int dx = 0;
		if (d3 == true)
			dx += egg.getWidth() / 10;
		egg.setPosition(x * (Gdx.graphics.getWidth() / mapx) + dx, y * (Gdx.graphics.getHeight() / mapy) + (Gdx.graphics.getHeight() / mapy) / 2);
		egg.draw(batch);
	}
	
}
