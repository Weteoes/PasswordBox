<template>
  <div class="dlg_form">
    <div class="only">
      <div class="title">当前共找到<span v-text="tableData.length"></span>条记录</div>
    </div>
    <div class="table">
      <el-table :data="tableData"
                :default-sort="{prop: 'host', order: 'ascending'}"
                height="400">
        <el-table-column prop="host"
                         label="域"
                         width="400"
                         sortable>
          <template slot-scope="scope">
            <span>{{ scope.row.host }}</span>
          </template>
        </el-table-column>
        <el-table-column prop="user"
                         label="用户名"
                         :filters="filters.user"
                         :filter-method="filterUserHandler"
                         sortable>
          <template slot-scope="scope">
            <span>{{ scope.row.user }}</span>
          </template>
        </el-table-column>
        <el-table-column label="密码">
          <template slot-scope="scope">
            <el-popover transition="el-zoom-in-top"
                        trigger="hover"
                        placement="left">
              <p>{{ scope.row.pass }}</p>
              <div slot="reference"
                   class="name-wrapper">
                <el-tag size="medium">******</el-tag>
              </div>
            </el-popover>
          </template>
        </el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button size="mini"
                       type="danger"
                       @click="tableDeleteRow(scope.$index, scope.row)">移除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.only {
  padding: 10px 10px 0 10px;
}

.title {
  height: 20px;
  margin: 5px 0 0 5px;
  font-size: 14px;
  color: #909399;
}

.table {
  width: 100%;
  height: 450px;
  padding: 10px;
  padding-top: 0;
  box-sizing: border-box;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      dlgTitle: '密码保管箱',
      dlgStyle: 'width: 900px', // 需要和readyCEFSize一起修改
      tableData: [], // 数据
      // 筛选规则
      filters: {
        user: []
      },
      element: {
        messageBox: null // 记录messagebox
      }
    }
  },
  methods: {
    ready () {
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.$parent.dlgStyle = this.dlgStyle // 样式
      this.$parent.$parent.readyCEFSize({ w: 900, div: '.dlg2_a' }) // 设置窗口大小
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.dlg2_aaa')) // 拖动条
      this.tableLoad() // 加载数据
      this.tableScroll() // Scroll事件
      this.readyDlgApi() // 设置窗口API回调
      // DEBUG（可以不执行，执行是为了调试，不影响使用）
      // 初始化筛选规则
      this.tableReadyFilter()
    },
    // 设置窗口API回调
    readyDlgApi () {
      // 窗口句柄回调
      this.w.softwareDlgApi.activate = (a) => {
        if (a !== 0) {
          // 重新加载表格
          this.tableLoad()
        }
      }
    },
    tableLoad () {
      this.w.basic.ajax(this.w.url.getAll, 'get', {},
        (r) => {
          const data = r.data
          if (data.Code === 0) {
            const tableData_ = []
            for (const i of data.List) {
              tableData_.push({ host: i.Host, user: i.User, pass: i.Pass })
            }
            this.tableData = tableData_
            // 初始化筛选规则
            this.tableReadyFilter()
          }
        }
      )
    },
    tableScroll () {
      document.querySelector('.el-table__body-wrapper').addEventListener('scroll', (r) => {
        const doms = document.querySelectorAll('.el-popover')
        for (const i of doms) {
          i.style.display = 'none'
        }
      })
    },
    tableDeleteRow (index, rows) {
      // 移除UI
      for (let i = 0; i < this.tableData.length; i++) {
        if (this.tableData[i].host === rows.host) {
          this.tableData.splice(i, 1)
        }
      }
      // 移除数据库
      const data = 'Host={0}'.format(rows.host)
      this.w.basic.ajax(this.w.url.del + data, 'get', {},
        (r) => {
          const data = r.data
          if (data.Code === 0) {
            this.showMessageBox('操作成功', 'success')
          } else {
            this.showMessageBox('操作失败', 'error')
            // 重新加载列表
            this.tableLoad()
          }
        }
      )
    },
    // 初始化筛选规则
    tableReadyFilter () {
      const userFilterList = []
      const userFilter = []
      for (const i of this.tableData) {
        // 判断是否存在于列表
        if (!userFilterList.includes(i.user)) {
          // 不存在就加入
          userFilterList.push(i.user)
          userFilter.push({ text: i.user, value: i.user })
        }
      }
      this.filters.user = userFilter
    },
    // user筛选
    filterUserHandler (value, row, column) {
      return value === row.user
    },
    showMessageBox (msg, type) {
      if (this.element.messageBox !== null) {
        this.element.messageBox.close()
      }
      this.element.messageBox = this.$message({
        showClose: true,
        message: msg,
        type: type
      })
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  mounted () {
    if (this.$store.state.debug) {
      window.debug = this
    }
    this.ready()
  }
}
</script>
