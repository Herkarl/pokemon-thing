//
// Created by Herman Karlsson on 2017-02-11.
//

#ifndef POKEMON_SIMULATION_STATE_H
#define POKEMON_SIMULATION_STATE_H

#include <vector>
#include <algorithm>
#include <utility>
#include "pokemon.h"
class state {
private:

	std::vector<std::vector<pokemon>> board;
	int height,width;
	std::vector<int> count;

public:

	void init(int,int);

	int type(int,int);

	void step();

	int get_count(int);

};

void state::init(int h, int w) {

	this->height = h;
	this->width  = w;
	this->board.assign(h, std::vector<pokemon>(w));
	this->count.assign(18,0);
	std::random_device tmp_rng;
	std::mt19937 rng(tmp_rng());

	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j){
			this->board[i][j].generate(rng);
			++this->count[this->board[i][j].get_type()];
		}

}

int state::type(int x, int y) {

	return this->board[x][y].get_type();

}

void state::step() {

	static std::vector<int> d_order = {0,1,2,3,4,5,6,7};
	static std::vector<int> dx = {1,1,1,0,0,-1,-1,-1};
	static std::vector<int> dy = {1,0,-1,1,-1,1,0,-1};

	std::vector<std::pair<int,int>> order;

	for(int i = 0; i < this->height; ++i)
		for(int j = 0; j < this->width; ++j){
			bool diff_neightbour = 0;
			for(int k = 0; k < 8; ++k){
				int ni = (i+dx[k]+this->height)%this->height;
				int nj = (j+dy[k]+this->width )%this->width;
				diff_neightbour |= (this->board[i][j].get_type() != this->board[ni][nj].get_type());
			}
			if(diff_neightbour) order.push_back({i,j});
			else this->board[i][j].heal(5);
		}

	std::sort(order.begin(), order.end(), [&](std::pair<int,int> a, std::pair<int,int> b) -> bool{
		int a_s = this->board[a.first][a.second].speed();
		int b_s = this->board[b.first][b.second].speed();
		if(a_s != b_s) return a_s < b_s;
		return this->board[a.first][a.second].hpmax() < this->board[b.first][b.second].hpmax();
	});

	std::vector<std::vector<bool>> changed(this->height,std::vector<bool>(this->width,0));
	for(std::pair<int,int> i:order) {

		if(changed[i.first][i.second]) continue;

		std::random_shuffle(d_order.begin(),d_order.end());

		int x = -1,y = -1, weak = 1e9;

		for(int j:d_order) {

			int nx = (i.first +dx[j]+this->height)%this->height;
			int ny = (i.second+dy[j]+this->width )%this->width;

			if(this->board[nx][ny].get_type() != this->board[i.first][i.second].get_type()) {
				int tmp = this->board[nx][ny].weakness(this->board[i.first][i.second]);
				if (tmp < weak)
					x = nx, y = ny, weak = tmp;
			}
		}

		if(x != -1) {

			this->board[i.first][i.second].fight(this->board[x][y]);

			if(this->board[x][y].health() <= 0) {

				--this->count[this->board[x][y].get_type()];

				this->board[x][y] = this->board[i.first][i.second];
				//this->board[x][y].heal(1000);
				changed[x][y] = true;

				++this->count[this->board[x][y].get_type()];
			}
		}
	}
}

int state::get_count(int type) {

	return this->count[type];

}

#endif //POKEMON_SIMULATION_STATE_H
