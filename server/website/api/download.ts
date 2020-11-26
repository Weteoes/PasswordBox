import request from '@/util/request'

export function downloadList() {
  return request({
    method: 'post',
    url: '/download/get',
  })
}

export function downloadLog(data: object) {
  return request({
    method: 'post',
    url: '/download/log',
    data,
  })
}
