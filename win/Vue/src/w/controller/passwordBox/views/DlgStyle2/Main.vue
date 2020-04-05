<template>
  <div class="dlg_form">
    <div class="table">
      <el-table :data="tableData" :default-sort="{prop: 'host', order: 'ascending'}" height="400">
        <el-table-column prop="host" label="域" sortable>
          <template slot-scope="scope">
            <span>{{ scope.row.host }}</span>
          </template>
        </el-table-column>
        <el-table-column prop="user" label="用户名" sortable>
          <template slot-scope="scope">
            <span>{{ scope.row.user }}</span>
          </template>
        </el-table-column>
        <el-table-column label="密码">
          <template slot-scope="scope">
            <el-popover transition="el-zoom-in-top" trigger="hover" placement="left">
              <p>{{ scope.row.pass }}</p>
              <div slot="reference" class="name-wrapper">
                <el-tag size="medium">******</el-tag>
              </div>
            </el-popover>
          </template>
        </el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button size="mini" type="danger" @click="tableDeleteRow(scope.$index, scope.row)">移除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.table {
  width: 100%;
  height: 450px;
  padding: 10px;
  box-sizing: border-box;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      dlgTitle: 'Password Box',
      tableData: [] // 数据
    }
  },
  methods: {
    ready () {
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.tableLoad() // 加载数据
      this.tableScroll() // Scroll事件
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.dlg2_aaa')) // 拖动条
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
      this.w.basic.ajax(this.w.url.del + data, 'get', { },
        (r) => {
          const data = r.data
          if (data.Code === 0) {
            this.$message({
              message: '操作成功',
              type: 'success'
            })
          } else {
            this.$message({
              message: '操作失败',
              type: 'error'
            })
            // 重新加载列表
            this.tableLoad()
          }
        }
      )
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
