package com.mygdx.game;

import java.util.Vector;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Main extends Game {
	public SpriteBatch batch;
	public Network net;
	public GameScreen game;
	public Map map = null;
	public Vector<Team> teams = new Vector<Team>();
	public Vector<Player> players = new Vector<Player>();
	public Vector<Explo> explos = new Vector<Explo>();
	public Vector<Eggs> eggs = new Vector<Eggs>();
	
	public boolean d3 = false;
	
	Sprite start;
	
	Sprite grass;
	
	Sprite bois;
	Sprite chaudron;
	Sprite minerai;
	Sprite nourriture;
	Sprite rubi;
	Sprite sable;
	Sprite saphir;
	
	Sprite d_down;
	Sprite d_up;
	Sprite d_right;
	Sprite d_left;
	
	Sprite incante;
	
	Sprite explo;
	
	Sprite broad;
	
	Sprite yoshi;
	
	
	int map_size_x;
	int map_size_y;
	
	@Override
	public void create() {
		// TODO Auto-generated method stub
		batch = new SpriteBatch();
		net = new Network(this);
		game = new GameScreen(this);
		
		Init_Sprite();
		
		this.setScreen(new MenuScreen(this));
	}
	
	void Change_level(int id, char level)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).id == id)
				players.get(i).level = level;
			i++;
		}
	}
	
	void PlayerDead(int id)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).id == id)
			{
				explos.addElement(new Explo(explo, players.get(i).x, players.get(i).y, map_size_x, map_size_y));
				players.remove(i);
			}
			i++;
		}
	}
	
	void Broad(int id)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).id == id)
				players.get(i).start_broad();
			i++;
		}
	}
	
	void movePlayer(int id, int x, int y, char o)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).id == id)
				players.get(i).move(x, y, o);
			i++;
		}
	}
	
	public void Take(int id)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).id == id)
				players.get(i).take_state = true;
			i++;
		}
	}
	
	public void Stop_Incante(int x, int y)
	{
		int i = 0;
		while (i < players.size())
		{
			if (players.get(i).x == x && players.get(i).y == y)
				players.get(i).inc_state = false;
			i++;
		}
	}
	
	public void Incante(Vector<Integer> ids)
	{
		int i = 0;
		while (i < players.size())
		{
			if (ids.contains(players.get(i).id))
				players.get(i).inc_state = true;
			i++;
		}
	}
	
	void Dead_Eggs(int id)
	{
		int i = 0;
		while (i < eggs.size())
		{
			if (eggs.get(i).id == id)
			{
				eggs.remove(i);
			}
			i++;
		}
	}
	
	public void Create_Eggs(int id, int x, int y)
	{
		eggs.addElement(new Eggs(yoshi, id, x, y, map_size_x, map_size_y));
	}
	
	public void Create_Player(int id, int x, int y, char o, char level, String team)
	{
		char[] color = {0,0,0};
		players.addElement(new Player(id,x,y,o,level, color, d_down, d_up , d_right, d_left, incante, broad, map_size_x, map_size_y));
	}
	
	public void Create_Map(int x, int y)
	{
		map_size_x = x;
		map_size_y = y;
		map = new Map(x, y, grass, bois, chaudron, minerai, nourriture, rubi, sable, saphir);
	}
	
	public void Store_res(int x, int y, Vector<Integer> res)
	{
		map.Store_Res(x, y, res);
	}
	
	public void Create_Team(String name)
	{
		teams.addElement(new Team(name));
	}

	public void render() {super.render();}
	
	public void dispose() {batch.dispose();}
	
	void Init_Sprite()
	{
		Texture startTexture = new Texture(Gdx.files.internal("acceuil.jpg"));
		
		Texture grassTexture = new Texture(Gdx.files.internal("grass.jpg"));
        
        Texture boisTexture = new Texture(Gdx.files.internal("bois.png"));
        Texture chaudronTexture = new Texture(Gdx.files.internal("chaudron.png"));
        Texture mineraiTexture = new Texture(Gdx.files.internal("minerai.png"));
        Texture nourritureTexture = new Texture(Gdx.files.internal("nourriture.png"));
        Texture rubiTexture = new Texture(Gdx.files.internal("rubi.png"));
        Texture sableTexture = new Texture(Gdx.files.internal("sable.png"));
        Texture saphirTexture = new Texture(Gdx.files.internal("saphir.png"));
        
        Texture d_downTexture = new Texture(Gdx.files.internal("d_down.png"));
        Texture d_upTexture = new Texture(Gdx.files.internal("d_up.png"));
        Texture d_rightTexture = new Texture(Gdx.files.internal("d_right.png"));
        Texture d_leftTexture = new Texture(Gdx.files.internal("d_left.png"));
        
        Texture incanteTexture = new Texture(Gdx.files.internal("incante.png"));
        
        Texture exploTexture = new Texture(Gdx.files.internal("explo.png"));
        
        Texture broadTexture = new Texture(Gdx.files.internal("broadcast.png"));
        
        Texture yoshiTexture = new Texture(Gdx.files.internal("yoshi.png"));
        
        yoshi = new Sprite(yoshiTexture);
        
        start = new Sprite(startTexture);
        
        grass = new Sprite(grassTexture);
        
        bois = new Sprite(boisTexture);
        chaudron = new Sprite(chaudronTexture);
        minerai = new Sprite(mineraiTexture);
        nourriture = new Sprite(nourritureTexture);
        rubi = new Sprite(rubiTexture);
        sable = new Sprite(sableTexture);
        saphir = new Sprite(saphirTexture);
        
        d_down = new Sprite(d_downTexture);
        d_up = new Sprite(d_upTexture);
        d_right = new Sprite(d_rightTexture);
        d_left = new Sprite(d_leftTexture);
        
        incante = new Sprite(incanteTexture);
        
        explo = new Sprite(exploTexture);
        
        broad = new Sprite(broadTexture);
	}
}
