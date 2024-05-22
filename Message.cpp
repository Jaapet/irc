#include "Message.hpp"

Message::Message() : sender(""), command(""), payload("")
{

}
void Message::clear()
{
	this->sender.clear();
	this->command.clear();
	this->params.clear();
	this->payload.clear();
}