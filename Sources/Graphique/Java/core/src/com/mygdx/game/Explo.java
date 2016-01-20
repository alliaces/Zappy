package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Explo {

	long time;
	long time_prev;
	int x;
	int y;
	int mapx;
	int mapy;
	Sprite explo;
	
	public void resize()
	{
		explo.setSize(Gdx.graphics.getWidth() / mapx, Gdx.graphics.getHeight() / mapy);
	}
	
	public Explo(Sprite explo, int x, int y, int mapx, int mapy)
	{
		this.explo = explo;
		this.x = x;
		this.y = y;
		this.mapx = mapx;
		this.mapy = mapy;
		explo.setSize(Gdx.graphics.getWidth() / mapx, Gdx.graphics.getHeight() / mapy);
		time = System.currentTimeMillis();
		time_prev = time;
	}
	
	public boolean update()
	{
		if (time - time_prev > 1000)
			return(false);
		else
		{
			time = System.currentTimeMillis();
			return(true);
		}
	}
	
	public void draw(SpriteBatch batch)
	{
		explo.setPosition(x * (Gdx.graphics.getWidth() / mapx), y * (Gdx.graphics.getHeight() / mapy));
		explo.draw(batch);
	}
	
}
