package com.mygdx.game;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Vector;

public class Network {

	Main game;
	Socket sock;
	boolean connect = false;
	BufferedReader in;
	PrintWriter out;
	
	public Network(Main game)
	{
		this.game = game;
	}
	
	boolean	connect(String addr)
	{
		if (connect)
			return true;
		String host = "";
		int port = 1212;
		if (!addr.contains(":"))
			host = addr;
		else
		{
			host = addr.split(":")[0];
			port = Integer.parseInt(addr.split(":")[1]);
		}
		try {
			System.out.println(host);
			sock = new Socket(host, port);
			in = new BufferedReader (new InputStreamReader (sock.getInputStream()));
			out = new PrintWriter(sock.getOutputStream());
			connect = true;
			new Thread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					execute();
				}
				
			}).start();
		} catch (UnknownHostException e) {
			//e.printStackTrace();
			return false;
		} catch (IOException e) {
			//e.printStackTrace();
			return false;
		}
		return true;
	}
	
	void execute()
	{
		String cmd;
		while (true)
		{
			try {
				cmd = in.readLine();
				Parse(cmd);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	void Parse(String cmd)
	{
		//System.out.println(cmd);
		if (cmd == null)
			System.exit(0);
		if (cmd.equals("BIENVENUE"))
			Welcome();
		if (cmd.contains(" "))
		{
			if (cmd.split(" ")[0].equals("msz"))
				Create_Map(cmd);
			if (cmd.split(" ")[0].equals("bct"))
				Store_res(cmd);
			if (cmd.split(" ")[0].equals("tna"))
				Create_Team(cmd);
			if (cmd.split(" ")[0].equals("ppo"))
				Move_Player(cmd);
			if (cmd.split(" ")[0].equals("pnw"))
				Create_Player(cmd);
			if (cmd.split(" ")[0].equals("pic"))
				Start_incante(cmd);
			if (cmd.split(" ")[0].equals("pie"))
				Stop_incante(cmd);
			if (cmd.split(" ")[0].equals("pdr"))
				Take(cmd);
			if (cmd.split(" ")[0].equals("pgt"))
				Take(cmd);
			if (cmd.split(" ")[0].equals("pdi"))
				Dead(cmd);
			if (cmd.split(" ")[0].equals("pbc"))
				Broad(cmd);
			if (cmd.split(" ")[0].equals("plv"))
				Change_level(cmd);
			if (cmd.split(" ")[0].equals("enw"))
				Create_Eggs(cmd);
			if (cmd.split(" ")[0].equals("eht"))
				Dead_Eggs(cmd);
		}
	}
	
	void Create_Eggs(String cmd)
	{
		int id = Integer.parseInt(cmd.split(" ")[1]);
		int x = Integer.parseInt(cmd.split(" ")[3]);
		int y = Integer.parseInt(cmd.split(" ")[4]);
		game.Create_Eggs(id, x, y);
	}
	
	void Dead_Eggs(String cmd)
	{
		int id = Integer.parseInt(cmd.split(" ")[1]);
		game.Dead_Eggs(id);
	}
	
	void Change_level(String cmd)
	{
		game.Change_level(Integer.parseInt(cmd.split(" ")[1]),(char)Integer.parseInt(cmd.split(" ")[2]));
	}
	
	void Welcome()
	{
		out.print("GRAPHIC\n");
		out.flush();
	}
	
	void Broad(String cmd)
	{
		game.Broad(Integer.parseInt(cmd.split(" ")[1]));
	}
	
	void Dead(String cmd)
	{
		game.PlayerDead(Integer.parseInt(cmd.split(" ")[1]));
	}
	
	void Take(String cmd)
	{
		game.Take(Integer.parseInt(cmd.split(" ")[1]));
	}
	
	void Create_Player(String cmd)
	{
		int id = Integer.parseInt(cmd.split(" ")[1]);
		int x = Integer.parseInt(cmd.split(" ")[2]);
		int y = Integer.parseInt(cmd.split(" ")[3]);
		int o = Integer.parseInt(cmd.split(" ")[4]);
		int l = Integer.parseInt(cmd.split(" ")[5]);
		String N = cmd.split(" ")[6];
		game.Create_Player(id, x, y, (char)o, (char)l, N);
	}
	
	void Start_incante(String cmd)
	{
		Vector<Integer> ids = new Vector<Integer>();
		int i = 4;
		while (i != cmd.split(" ").length)
		{
			ids.addElement(Integer.parseInt(cmd.split(" ")[i]));
			i++;
		}
		game.Incante(ids);
	}
	
	void Stop_incante(String cmd)
	{
		game.Stop_Incante(Integer.parseInt(cmd.split(" ")[1]), Integer.parseInt(cmd.split(" ")[2]));
	}
	
	void Create_Team(String cmd)
	{
		game.Create_Team(cmd.split(" ")[1]);
	}
	
	void Move_Player(String cmd)
	{
		int id = Integer.parseInt(cmd.split(" ")[1]);
		int x = Integer.parseInt(cmd.split(" ")[2]);
		int y = Integer.parseInt(cmd.split(" ")[3]);
		int o = Integer.parseInt(cmd.split(" ")[4]);
		game.movePlayer(id, x, y, (char)o);
	}
	
	void Store_res(String cmd)
	{
		int x = Integer.parseInt(cmd.split(" ")[1]);
		int y = Integer.parseInt(cmd.split(" ")[2]);
		int a = Integer.parseInt(cmd.split(" ")[3]);
		int b = Integer.parseInt(cmd.split(" ")[4]);
		int c = Integer.parseInt(cmd.split(" ")[5]);
		int d = Integer.parseInt(cmd.split(" ")[6]);
		int e = Integer.parseInt(cmd.split(" ")[7]);
		int f = Integer.parseInt(cmd.split(" ")[8]);
		int g = Integer.parseInt(cmd.split(" ")[9]);
		Vector<Integer> store = new Vector<Integer>();
		store.add(a);
		store.add(b);
		store.add(c);
		store.add(d);
		store.add(e);
		store.add(f);
		store.add(g);
		game.Store_res(x, y, store);
	}
	
	void Create_Map(String cmd)
	{
		game.Create_Map(Integer.parseInt(cmd.split(" ")[1]), Integer.parseInt(cmd.split(" ")[2]));
	}
	
}
