#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include <functional>
#include <cassert>
#include <unistd.h>

Connection::Connection(int fd, EventLoop *loop) {
    socket_ = std::make_unique<Socket>();
    socket_->set_fd(fd);
    channel_ = std::make_unique<Channel>(fd, loop);
    std::function<void()> cb = std::bind(&Connection::Recv, this);
    channel_->set_read_callback(cb);
    assert( channel_->EnableRead() == RC_SUCCESS );
}

Connection::~Connection() {}

std::unique_ptr<Socket> &Connection::socket() { return socket_; }

void Connection::set_delete_connection_callback(std::function<void(int)> fn) { delete_connection_callback_ = std::move(fn); }

void Connection::set_recv_callback(std::function<void(Connection *)> fn) { recv_callback_ = std::move(fn); }

const std::string &Connection::recv_buf() const {
    return recv_buf_;
}

void Connection::set_send_buf(std::string send_buf) {
    send_buf_ = std::move(send_buf);
}

RC Connection::Recv() {
    recv_buf_.clear();
    if (socket_->IsNonBlocking()) {
        assert( RecvNonBlocking() == RC_SUCCESS );
    } else {
        assert( RecvBlocking() == RC_SUCCESS );
    }
    if (recv_callback_) {
        recv_callback_(this);
    }
    return RC_SUCCESS;
}

RC Connection::RecvBlocking() {
    int fd = socket_->fd();
    int data_size = socket_->RecvBufSize();
    char buf[data_size];
    memset(buf, 0, data_size);
    ssize_t bytes_read = ::read(fd, buf, data_size);
    assert( bytes_read == -1 || bytes_read == data_size );
    if(bytes_read == 0) {
        delete_connection_callback_(fd);
        recv_callback_ = nullptr;
    } else if (bytes_read == -1){
        if (errno == ECONNRESET) {
            delete_connection_callback_(fd);
            recv_callback_ = nullptr;
            return RC_SUCCESS;
        }
        perror("Failed to read fd");
        return RC_CONNECTION_ERROR;
    }
    recv_buf_.assign(buf);
    return RC_SUCCESS;
}

RC Connection::RecvNonBlocking() {
    return RC_UNIMPLEMENTED;
}

RC Connection::Send() {
    if (socket_->IsNonBlocking()) {
        assert( SendNonBlocking() == RC_SUCCESS );
    } else {
        assert( SendBlocking() == RC_SUCCESS );
    }
    send_buf_.clear();
    return RC_SUCCESS;
}
RC Connection::SendBlocking() {
    int fd = socket_->fd();
    ssize_t bytes_write = ::write(fd, send_buf_.c_str(), send_buf_.size());
    assert(bytes_write == send_buf_.size() );
    if (bytes_write == -1){
        perror("Failed to write fd");
        return RC_CONNECTION_ERROR;
    }
    return RC_SUCCESS;
}
RC Connection::SendNonBlocking() {
    return RC_UNIMPLEMENTED;
}