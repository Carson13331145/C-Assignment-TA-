#include <iostream>
using namespace std;
#define MAX_FRIEND 99
#define MAX_COUNT 100

static int total_person = 0;

struct person {
	int id, friend_count, friends[MAX_FRIEND];
	person() {
		id = total_person++;
		friend_count = 0;
	}
	bool addFriend(int _id) {
		for (int i = 0; i < friend_count; i++)
			if (friends[i] == _id) return false;
		friends[friend_count++] = _id;
		return true;
	}
	bool deleteFriend(int _id) {
		for (int i = 0; i < friend_count; i++)
			if (friends[i] == _id) {
				friend_count--;
				for (int j = i; j < friend_count; j++)
					friends[j] = friends[j+1];
				return true;
			}
		return false;
	}
};

// type_0: everybody is strange to each other at first
// type_1: everybody is known to each other at first
class group {
	int person_count, type;
	person member[MAX_COUNT];
public:
	group(int _type) {
		type = _type;
		person_count = 0;
	}
	~group() {}
	void displayGroup() {
		for (int i = 0; i < person_count; i++) {
			cout << "Person_" << member[i].id << ": ";
			for (int j = 0; j < member[i].friend_count-1; j++)
				cout << member[i].friends[j] << ", ";
			if (member[i].friend_count)
				cout << member[i].friends[member[i].friend_count-1] << "\n";
			else cout << "null\n";
		}
	}
	bool addMember(person &p) {
		for (int i = 0; i < person_count; i++)
			if (member[i].id == p.id) return false;
		member[person_count++] = p;
		for (int i = 0; type && i < person_count-1; i++)
			makeFriend(member[i], member[person_count-1]);
		return true;
	}
	bool deleteMember(person &p) {
		for (int i = 0; i < person_count; i++)
			if (member[i].id == p.id) {
				person_count--;
				for (int j = i; j < person_count; j++)
					member[j] = member[j+1];
				return true;
			}
		return false;
	}
	bool makeFriend(person &p1, person &p2) {
		int a = -1, b = -1;
		for (int i = 0; i < person_count; i++)
			if (member[i].id == p1.id) a = i;
			else if (member[i].id == p2.id) b = i;
		if (a == -1 || b == -1) return false;
		else return member[a].addFriend(member[b].id) &&
			member[b].addFriend(member[a].id);
	}
	bool breakRelation(person &p1, person &p2) {
		int a = -1, b = -1;
		for (int i = 0; i < person_count; i++)
			if (member[i].id == p1.id) a = i;
			else if (member[i].id == p2.id) b = i;
		if (a == -1 || b == -1) return false;
		else return member[a].deleteFriend(member[b].id) &&
			member[b].deleteFriend(member[a].id);
	}
};
