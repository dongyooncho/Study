#include<iostream>
using namespace std;

#include<flatbuffers/flatbuffers.h>
#include"lib/playerInfo_generated.h"

int main()
{
	cout<<"CHANGE"<<endl;
	flatbuffers::FlatBufferBuilder builder;
	auto name = builder.CreateString("Foo");
	int level = 99;
	builder.Finish(CreatePlayerInfo(builder, name, level));

	const uint8_t* data = builder.GetBufferPointer();
	int builderSize = builder.GetSize();

	const PlayerInfo* plyaerinfo = GetPlayerInfo(data);
	

	cout << "name: " << plyaerinfo->name()->str()<< endl;
	cout << "level: " << plyaerinfo->level()<< endl;
	
	return 0;
}
