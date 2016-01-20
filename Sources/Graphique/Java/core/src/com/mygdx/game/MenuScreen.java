package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.TextInputListener;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;

public class MenuScreen implements Screen, TextInputListener {

	Main game;
	OrthographicCamera camera;
	String text;
	
	public MenuScreen(Main main)
	{
		this.game = main;
		camera = new OrthographicCamera();
        camera.setToOrtho(false, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        game.start.setSize(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        Gdx.input.getTextInput(this, "Connection", text, "");
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
        
        game.start.draw(game.batch);
        
        game.batch.end();
	}

	@Override
	public void resize(int width, int height) {
		// TODO Auto-generated method stub
		game.start.setSize(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
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

	@Override
	public void input(String text) {
		// TODO Auto-generated method stub
		this.text = text;
		//connection
		if (game.net.connect(text))
		{
			if (text.contains(":") && text.split(":").length == 3 && text.split(":")[2].equals("true"))
				game.d3 = true;
			else
				game.d3 = false;
			game.setScreen(game.game);
		}
		else
		{
			text = "";
			Gdx.input.getTextInput(this, "Connection", text, "Retry");
		}
	}

	@Override
	public void canceled() {
		// TODO Auto-generated method stub
		text = "";
		Gdx.input.getTextInput(this, "Connection", text, "Retry");
	}

}
