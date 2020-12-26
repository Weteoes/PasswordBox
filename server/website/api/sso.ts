import request from '@/util/request'

export function getInfo() {
  return request({
    method: 'post',
    url: '/sso/login',
  })
}
