package com.mygdx.game;

import java.util.Vector;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;

public class GameScreen implements Screen {

	Main game;
	OrthographicCamera camera;
	
	public GameScreen(Main main)
	{
		game = main;
		camera = new OrthographicCamera();
        camera.setToOrtho(false, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());    
	}
	
	@Override
	public void show() {
		// TODO Auto-generated method stub

	}

	@Override
	public void render(float delta) {
		// TODO Auto-generated method stub
		Gdx.gl.glClearColor(0, 0, 0, 1);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        camera.update();
        game.batch.setProjectionMatrix(camera.combined);

        game.batch.begin();
        if (game.d3 == false)
        {
        	draw();
        }
        else
        {
        	Gdx.gl.glColorMask(true, false, false, true);
        	draw();
        	Gdx.gl.glClear(Gdx.gl.GL_DEPTH_BUFFER_BIT);
        	Gdx.gl.glColorMask(false, true, true, true);
        	effect();
            draw();
            reset_effect();
            Gdx.gl.glColorMask(true, true, true, true);
        }
        game.batch.end();
	}
	
	void effect()
	{
		if (game.map != null)
			game.map.d3 = true;
		int i = 0;
    	while (i < game.players.size())
    	{
    		game.players.elementAt(i).d3 = true;
    		i++;
    	}
    	i = 0;
    	while (i < game.eggs.size())
    	{
    		game.eggs.elementAt(i).d3 = true;
    		i++;
    	}
	}
	
	void reset_effect()
	{
		if (game.map != null)
			game.map.d3 = false;
		int i = 0;
    	while (i < game.players.size())
    	{
    		game.players.elementAt(i).d3 = false;
    		i++;
    	}
    	i = 0;
    	while (i < game.eggs.size())
    	{
    		game.eggs.elementAt(i).d3 = false;
    		i++;
    	}
	}
	
	void draw()
	{
		if (game.map != null)
    		game.map.draw(game.batch);
    	int i = 0;
    	while (i < game.eggs.size())
    	{
    		game.eggs.elementAt(i).draw(game.batch);
    		i++;
    	}
    	i = 0;
    	while (i < game.explos.size())
    	{
    		if (game.explos.elementAt(i).update() == false)
    			game.explos.remove(i);
    		else
    			game.explos.elementAt(i).draw(game.batch);
    		i++;
    	}
    	i = 0;
    	while (i < game.players.size())
    	{
    		game.players.elementAt(i).draw_player(game.batch);
    		i++;
    	}
	}

	@Override
	public void resize(int width, int height) {
		// TODO Auto-generated method stub
		 camera.setToOrtho(false, Gdx.graphics.getWidth(), Gdx.graphics.getHeight()); 
		if (game.map != null)
        	game.map.resize();
		int i = 0;
        while (i < game.explos.size())
        {
        		game.explos.elementAt(i).resize();
        	i++;
        }
        i = 0;
        while (i < game.players.size())
        {
        	game.players.elementAt(i).resize();
        	i++;
        }
        i = 0;
        while (i < game.eggs.size())
        {
        	game.eggs.elementAt(i).resize();
        	i++;
        }
	}

	@Override
	public void pause() {
		// TODO Auto-generated method stub

	}

	@Override
	public void resume() {
		// TODO Auto-generated method stub

	}

	@Override
	public void hide() {
		// TODO Auto-generated method stub

	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub

	}

}
