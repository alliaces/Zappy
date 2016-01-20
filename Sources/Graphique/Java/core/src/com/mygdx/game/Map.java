package com.mygdx.game;

import java.util.Vector;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Map {
	
	Sprite grass;
	
	Sprite bois;
	Sprite chaudron;
	Sprite minerai;
	Sprite nourriture;
	Sprite rubi;
	Sprite sable;
	Sprite saphir;
	
	int sizex;
	int sizey;
	int content[][][];
	public boolean d3 = false;
	
	public void resize()
	{
		this.grass.setSize(Gdx.graphics.getWidth() / sizex, Gdx.graphics.getHeight() / sizey);
		this.bois.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.chaudron.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.minerai.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.nourriture.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.rubi.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.sable.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
		this.saphir.setSize((Gdx.graphics.getWidth() / sizex) / 7, (Gdx.graphics.getHeight() / sizey) / 7);
	}
	
	public Map(int x, int y, Sprite grass, Sprite bois, Sprite chaudron, Sprite minerai, Sprite nourriture, Sprite rubi, Sprite sable, Sprite saphir)
	{
		sizex = x;
		sizey = y;
		
		this.grass = grass;
		this.bois = bois;
		this.chaudron = chaudron;
		this.minerai = minerai;
		this.nourriture = nourriture;
		this.rubi = rubi;
		this.sable = sable;
		this.saphir = saphir;
		
		this.grass.setSize(Gdx.graphics.getWidth() / x, Gdx.graphics.getHeight() / y);
		this.bois.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.chaudron.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.minerai.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.nourriture.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.rubi.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.sable.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		this.saphir.setSize((Gdx.graphics.getWidth() / x) / 7, (Gdx.graphics.getHeight() / y) / 7);
		
		content = new int[x][y][7];
		
		int i = 0;
		int j = 0;
		int e = 0;
		
		while (i != x)
		{
			j = 0;
			while (j != y)
			{
				e = 0;
				while (e != 7)
				{
					content[i][j][e] = 0;
					e++;
				}
				j++;
			}
			i++;
		}
	}
	
	public void Store_Res(int x, int y, Vector<Integer> res)
	{
		int i = 0;
		while (i != 7)
		{
			content[x][y][i] = res.get(i);
			i++;
		}
	}
	
	public void draw(SpriteBatch batch)
	{
		int i = 0;
		int j = 0;
		
		while (i != sizex)
		{
			j = 0;
			while (j != sizey)
			{
				grass.setPosition(i * (Gdx.graphics.getWidth() / sizex), j * (Gdx.graphics.getHeight() / sizey));
				grass.draw(batch);
				j++;
			}
			i++;
		}
		
		i = 0;
		j = 0;
		int e = 0;
		
		while (i != sizex)
		{
			j = 0;
			while (j != sizey)
			{
				e = 0;
				while (e != 7)
				{
					if (content[i][j][e] > 0)
						draw_res(batch, e, i, j);
					e++;
				}
				j++;
			}
			i++;
		}
	}

	void draw_res(SpriteBatch batch, int e, int x, int y)
	{
		int dx = 0;
		if (d3 == true)
			dx += bois.getWidth() / 3;
		if (e == 0)
		{
			bois.setPosition(((x) * grass.getWidth()) + bois.getWidth() / 2 + dx, y * grass.getHeight() + bois.getWidth() / 2);
			bois.draw(batch);
		}
		else if (e == 1)
		{
			chaudron.setPosition(((x) * grass.getWidth()) + bois.getWidth() / 2 + dx, (y * grass.getHeight()) + grass.getHeight() - bois.getHeight() * 1.5f);
			chaudron.draw(batch);
		}
		else if (e == 2)
		{
			minerai.setPosition(((x) * grass.getWidth()) + bois.getWidth() * 5 + dx, y * grass.getHeight() + bois.getWidth() / 2);
			minerai.draw(batch);
		}
		else if (e == 3)
		{
			nourriture.setPosition(((x) * grass.getWidth()) + bois.getWidth() * 3 + dx, y * grass.getHeight() + bois.getWidth() / 2);
			nourriture.draw(batch);
		}
		else if (e == 4)
		{
			rubi.setPosition(((x) * grass.getWidth()) + bois.getWidth() * 3 + dx, y * grass.getHeight() + bois.getWidth() * 2.5f);
			rubi.draw(batch);
		}
		else if (e == 5)
		{
			sable.setPosition(((x) * grass.getWidth()) + bois.getWidth() * 3 + dx, (y * grass.getHeight()) + grass.getHeight() - bois.getHeight() * 1.5f);
			sable.draw(batch);
		}
		else if (e == 6)
		{
			saphir.setPosition(((x) * grass.getWidth()) + bois.getWidth() * 5 + dx, (y * grass.getHeight())+ grass.getHeight() - bois.getHeight() * 1.5f);
			saphir.draw(batch);
		}
	}

}
