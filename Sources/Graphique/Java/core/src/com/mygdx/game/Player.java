package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;

public class Player {

	Sprite current;
	Sprite down;
	Sprite up;
	Sprite right;
	Sprite left;
	
	Sprite incante;
	
	Sprite broad;
	
	boolean d3 = false;
	
	int id;
	int x;
	int y;
	char orient;
	char level;
	char[] color;
	int mapx;
	int mapy;
	
	long time;
	long time_prev;
	
	boolean inc_state = false;
	boolean take_state = false;
	boolean broad_state = false;
	
	public void resize()
	{
		this.down.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.broad.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.up.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.right.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.left.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.incante.setSize(Gdx.graphics.getWidth() / mapx, Gdx.graphics.getHeight() / mapy);
	}
	
	public Player(int id, int x, int y, char orient, char level, char[] color, Sprite down, Sprite up, Sprite right, Sprite left, Sprite incante, Sprite broad, int mapx, int mapy)
	{
		this.id = id;
		this.x = x;
		this.y = y;
		this.orient = orient;
		this.level = level;
		this.color = color;
		this.down = down;
		this.up = up;
		this.right = right;
		this.left = left;
		this.incante = incante;
		this.broad = broad;
		
		current = down;
		this.mapx = mapx;
		this.mapy = mapy;
		this.down.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.broad.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.up.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.right.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		this.left.setSize((Gdx.graphics.getWidth() / mapx) / 2, (Gdx.graphics.getHeight() / mapy) / 2);
		
		this.incante.setSize(Gdx.graphics.getWidth() / mapx, Gdx.graphics.getHeight() / mapy);
		
		time = System.currentTimeMillis();
		time_prev = time;
	}
	
	void move(int x, int y, char o)
	{
		this.x = x;
		this.y = y;
		this.orient = o;
	}
	
	void start_broad()
	{
		time = System.currentTimeMillis();
		time_prev = time;
		broad_state = true;
	}
	
	public void draw_player(SpriteBatch batch)
	{
		if (take_state == false)
		{
			if (orient == 1)
				current = down;
			if (orient == 2)
				current = right;
			if (orient == 3)
				current = up;
			if (orient == 4)
				current = left;
		}
		else
		{
				if (current == up && orient == 1)
					take_state = false;
				else if (current == right && orient == 2)
					take_state = false;
				else if (current == down && orient == 3)
					take_state = false;
				else if (current == left && orient == 4)
					take_state = false;
				else if (current == down)
					current = left;
				else if (current == left)
					current = up;
				else if (current == up)
					current = right;
				else if (current == right)
					current = down;
				time_prev = time;
		}
		if (inc_state == true)
		{
			int dx = 0;
			if (d3)
				dx += incante.getWidth() / 10;
			incante.setPosition(((x) * Gdx.graphics.getWidth() / mapx) + dx, ((y) * Gdx.graphics.getHeight() / mapy));
			incante.draw(batch);
		}
		if (level == 1)
			current.setColor(Color.WHITE);
		if (level == 2)
			current.setColor(Color.RED);
		if (level == 3)
			current.setColor(Color.GREEN);
		if (level == 4)
			current.setColor(Color.CYAN);
		if (level == 5)
			current.setColor(Color.ORANGE);
		if (level == 6)
			current.setColor(Color.PINK);
		if (level == 8)
			current.setColor(Color.PURPLE);
		if (level == 7)
			current.setColor(Color.YELLOW);
		int dx = 0;
		if (d3)
			dx += current.getWidth() / 10;
		current.setPosition(((x) * Gdx.graphics.getWidth() / mapx) + current.getWidth() / 2 + dx, ((y) * Gdx.graphics.getHeight() / mapy) + current.getHeight() / 2);
		current.draw(batch);
		if (broad_state == true)
		{
			dx = 0;
			if (d3)
				dx += broad.getWidth() / 10;
			if (time - time_prev > 500)
				broad_state = false;
			broad.setPosition(((x) * Gdx.graphics.getWidth() / mapx) + broad.getWidth() / 2 + dx, ((y) * Gdx.graphics.getHeight() / mapy) + broad.getHeight());
			broad.draw(batch);
			time = System.currentTimeMillis();
		}
	}
}