#include<iostream>

namespace DLL {
	struct DLV
	{
		DLV* first = nullptr;
		std::string middle;
		DLV* last = nullptr;
	};

	enum STATE
	{
		all,
		first,
		middle,
		last
	};


	class List
	{
	public:

		List(std::string str) {
			DLV* dlv = create(str);
			link = dlv;
		}
		~List() {
			STATE state = getState();
			if (state == all)
				delete link;
			else {
				goToStart();
				bool someLeft = remove();
				while (someLeft)
					someLeft = remove();
				delete link;
			}
		}

		bool addNext(std::string str) {
			if (link->last == nullptr)
			{
				DLV* dlv = create(str);
				dlv->first = link;
				link->last = dlv;
				link = dlv;
				return true;
			}
			return false;
		}

		bool addBack(std::string str) {
			if (link->first == nullptr)
			{
				DLV* dlv = create(str);
				dlv->last = link;
				link->first = dlv;
				link = dlv;
				return true;
			}
			return false;
		}

		void change(std::string str) {
			link->middle = str;
		}

		void print() {
			std::cout << link << ": " << link->middle << std::endl;
		}

		bool goBack() {
			if (link->first != nullptr) {
				link = link->first;
				return true;
			}
			return false;
		}

		bool goNext() {
			if (link->last != nullptr) {
				link = link->last;
				return true;
			}
			return false;
		}

		STATE getState() {
			return state(link);
		}

		DLV get() {
			return *link;
		}

		bool remove() {

			switch (getState())
			{
			case first:
			{
				DLV* lastDLV = link->last;
				lastDLV->first = nullptr;
				delete link;
				link = lastDLV;
				return true;
			}
			case last:
			{
				DLV* firstDLV = link->first;
				firstDLV->last = nullptr;
				delete link;
				link = firstDLV;
				return true;
			}
			case middle:
			{
				DLV* firstDLV = link->first;
				DLV* lastDLV = link->last;
				delete link;
				firstDLV->last = lastDLV;
				lastDLV->first = lastDLV;
				link = lastDLV;
				return true;
			}
			default:
				return false;
			}
		}

		bool goToStart() {
			STATE state = getState();
			if (state != first && state != all) {
				bool notAtStart = goBack();
				while (notAtStart)
					notAtStart = goBack();
				return true;
			}
			return false;
		}

	private:
		DLV* link;

		DLV* create(std::string str) {
			DLV* dlv = new DLV;
			dlv->middle = str;
			return dlv;
		}

		STATE state(DLV* dlv) {
			if (dlv->first == nullptr && dlv->last != nullptr)
				return first;
			if (dlv->first != nullptr && dlv->last == nullptr)
				return last;
			if (dlv->first != nullptr && dlv->last != nullptr)
				return middle;
			return all;
		}
	};
}

int main() {
	DLL::List list("wow");
	list.print();
	list.addNext("wtf?");
	list.print();
	list.goToStart();
	list.print();
	return 0;
}