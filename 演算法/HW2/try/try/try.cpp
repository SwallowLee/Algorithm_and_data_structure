#include <msgpack.hpp>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int main(void) {
	fstream input, output;
	size_t off = 0;
	int bufsize, num, i;
	char *buf = NULL;
	msgpack::sbuffer sbuf;

	input.open("input.txt", fstream::in | fstream::binary);

	input.seekg(0, ios::end);
	bufsize = input.tellg();
	input.seekg(0);

	buf = new char[bufsize];
	input.read(buf, bufsize);

	msgpack::object_handle oh;
	oh = msgpack::unpack(buf, bufsize, off);
	oh.get().convert(num);
	for (i = 0; i < num; i++)
	{
		vector<int> arr;
		msgpack::object_handle oh;
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(arr);
		sort(arr.begin(), arr.end());
		msgpack::pack(sbuf, arr);
	}
	delete[] buf;
	input.close();
	output.open("output.txt", fstream::out | fstream::binary);

	output.write(sbuf.data(), sbuf.size());
	output.close();
	return 0;

}